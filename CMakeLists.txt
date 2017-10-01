cmake_minimum_required (VERSION 2.6)
project (RaceTheMoon)

#set c++ standard
set (CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

# add the binary tree to the search path for include files
include_directories ("${PROJECT_BINARY_DIR}")

include(DownloadProject.cmake)

#add_subdirectory (external)

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

add_subdirectory(glew)

#include_directories(external/glew-1.13.0/include)
set(GLEW_SOURCE
        ${glew_SOURCE_DIR}/glew.c
        )

#get glm
download_project(PROJ glm
  GIT_REPOSITORY      https://github.com/g-truc/glm.git
  GIT_TAG             6a1e2ec
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
include_directories("${glm_SOURCE_DIR}")

add_definitions(-DGLEW_STATIC)
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            -lGL -lGLU -lXrandr -lXext -lX11 -lrt
            ${CMAKE_DL_LIBS}
            ${GLFW_LIBRARIES}
            )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            ${CMAKE_DL_LIBS}
            ${GLFW_LIBRARIES}
            )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Add all files from a src folder
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(RaceTheMoon ${SOURCES} src/main.cpp src/glfw.h)
#target_link_libraries (RaceTheMoon  ${EXTRA_LIBS})

set(GLEW_HEADERS
        )


add_library( GLEW_1130 STATIC
        ${GLEW_SOURCE}
        ${GLEW_INCLUDE}
        )

target_link_libraries(GLEW_1130
        ${OPENGL_LIBRARY}
        ${EXTRA_LIBS}
        )

target_link_libraries(RaceTheMoon glfw glm GLEW_1130)


