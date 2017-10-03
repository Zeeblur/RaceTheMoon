cmake_minimum_required (VERSION 2.6)
project (RaceTheMoon)

#set c++ standard
set (CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

# add the binary tree to the search path for include files
include_directories ("${PROJECT_BINARY_DIR}")

include(DownloadProject.cmake)

# don't download glfw project shit
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_DOCUMENT_INTERNALS "" OFF)
option(GLFW_INSTALL "" OFF)

#get glfw
download_project(PROJ glfw
  GIT_REPOSITORY      https://github.com/glfw/glfw.git
  GIT_TAG             0f488ac
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
include_directories("${glfw_SOURCE_DIR}/include")

#get glew
download_project(PROJ glew
  GIT_REPOSITORY      https://github.com/menpo/glew.git
  GIT_TAG             896c62c
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
include_directories("${glew_SOURCE_DIR}/include")

## get library for os
GET_DIRECTORY_PROPERTY(glew DIRECTORY ${glew_SOURCE_DIR} DEFINITION GLEW_NAME)

#get glm
download_project(PROJ glm
  GIT_REPOSITORY      https://github.com/g-truc/glm.git
  GIT_TAG             6a1e2ec
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
include_directories("${glm_SOURCE_DIR}")

find_package(OpenGL REQUIRED)

add_definitions(-DGLEW_STATIC)
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(glew
            ${OPENGL_LIBRARIES}
            -lGL -lGLU -lXrandr -lXext -lX11 -lrt
            ${CMAKE_DL_LIBS}
	    glm
	    ${glew}
            )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(glew
            ${OPENGL_LIBRARIES}
            ${CMAKE_DL_LIBS}
	    glm
	    ${glew}
            )
elseif()
    set(glew
	    glm
	    ${glew}
            )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Add all files from a src folder
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(RaceTheMoon ${SOURCES} src/main.cpp src/glfw.h)

target_link_libraries(RaceTheMoon glfw ${glew})


