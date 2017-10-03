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

#get glm
download_project(PROJ glm
  GIT_REPOSITORY      https://github.com/g-truc/glm.git
  GIT_TAG             6a1e2ec
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
include_directories("${glm_SOURCE_DIR}")

#get zlib
download_project(PROJ zlib
  GIT_REPOSITORY	  https://github.com/madler/zlib.git
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

add_subdirectory(${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
include_directories("${zlib_SOURCE_DIR}")

# TODO: fix this
set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIR} ${zlib_BINARY_DIR})
set(ZLIB_LIBRARY ${ZLIB_LIBRARY} ${zlib_SOURCE_DIR})

#get libpng
download_project(PROJ libpng
  GIT_REPOSITORY	  https://github.com/glennrp/libpng.git
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
add_subdirectory(${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})
include_directories("${zlib_SOURCE_DIR}")

# TODO: fix this
set(PNG_INCLUDE_DIR ${PNG_INCLUDE_DIR} ${libpng_BINARY_DIR})
set(PNG_LIBRARY ${PNG_LIBRARY} ${libpng_SOURCE_DIR})

#get libjpeg

download_project(PROJ libjpeg
  GIT_REPOSITORY	  https://github.com/LuaDist/libjpeg.git
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
add_subdirectory(${libjpeg_SOURCE_DIR} ${libjpeg_BINARY_DIR})
include_directories("${libjpeg_SOURCE_DIR}")

# TODO: fix this
set(JPEG_INCLUDE_DIR ${JPEG_INCLUDE_DIR} ${libjpeg_BINARY_DIR})
set(JPEG_LIBRARY ${JPEG_LIBRARY} ${libjpeg_SOURCE_DIR})

#freeimage options
option(ENABLE_TIFF "" OFF)
option(ENABLE_WEBP "" OFF)
option(ENABLE_RAW "" OFF)
option(ENABLE_OPENJP "" OFF)
option(FREEIMAGE_BUILD_STATIC "" OFF)
option(FREEIMAGE_BUILD_DLL "" ON)

#get freeimage
download_project(PROJ FreeImage
  GIT_REPOSITORY	  https://github.com/imazen/freeimage.git
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)



add_subdirectory(${FreeImage_SOURCE_DIR} ${FreeImage_BINARY_DIR})
include_directories("${FreeImage_SOURCE_DIR}/Source")

#target_link_libraries(RaceTheMoon FreeImage zlib libpng libjpeg)

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


set(GLEW_HEADERS
        )


target_link_libraries(RaceTheMoon glfw glm glew32 FreeImage zlib libpng libjpeg)
add_dependencies(RaceTheMoon glfw glm glew32 FreeImage zlib libpng libjpeg)

