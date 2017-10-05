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


#---------------- ASSIMP
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)

set(ASSIMP_BUILD_MDC_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_3DS_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_AC_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASE_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSBIN_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSXML_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_B3D_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_BVH_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_COLLADA_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_DXF_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_CSM_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_HMP_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_IRRMESH_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_IRR_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_LWO_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_LWS_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_MD2_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_MD3_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_MD5_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_MDC_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_MDL_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_NFF_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_NDO_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OFF_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_OBJ_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OGRE_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OPENGEX_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_PLY_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_MS3D_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_COB_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_BLEND_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_IFC_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_XGL_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_Q3D_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_Q3BSP_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_RAW_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SIB_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SMD_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_STL_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TERRAGEN_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_3D_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_X_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_3MF_IMPORTER OFF CACHE BOOL "" FORCE)
#set(addGTest_FOUND OFF CACHE BOOL "" FORCE)
set(BuildTests OFF CACHE BOOL "" FORCE)

download_project(PROJ assimp
        GIT_REPOSITORY      https://github.com/assimp/assimp
        GIT_TAG             a8673d4
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )
add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
include_directories("${assimp_SOURCE_DIR}")

#---------------- ASSIMP

# #get zlib
# download_project(PROJ zlib
  # GIT_REPOSITORY	  https://github.com/madler/zlib.git
  # ${UPDATE_DISCONNECTED_IF_AVAILABLE}
# )

# add_subdirectory(${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
# include_directories("${zlib_SOURCE_DIR}")

# # TODO: fix this
# set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIR} ${zlib_BINARY_DIR})
# set(ZLIB_LIBRARY ${ZLIB_LIBRARY} ${zlib_SOURCE_DIR})

# #get libpng
# download_project(PROJ libpng
  # GIT_REPOSITORY	  https://github.com/glennrp/libpng.git
  # ${UPDATE_DISCONNECTED_IF_AVAILABLE}
# )
# add_subdirectory(${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})
# include_directories("${zlib_SOURCE_DIR}")

# # TODO: fix this
# set(PNG_INCLUDE_DIR ${PNG_INCLUDE_DIR} ${libpng_BINARY_DIR})
# set(PNG_LIBRARY ${PNG_LIBRARY} ${libpng_SOURCE_DIR})

# #get libjpeg

# download_project(PROJ libjpeg
  # GIT_REPOSITORY	  https://github.com/LuaDist/libjpeg.git
  # ${UPDATE_DISCONNECTED_IF_AVAILABLE}
# )
# add_subdirectory(${libjpeg_SOURCE_DIR} ${libjpeg_BINARY_DIR})
# include_directories("${libjpeg_SOURCE_DIR}")

# # TODO: fix this
# set(JPEG_INCLUDE_DIR ${JPEG_INCLUDE_DIR} ${libjpeg_BINARY_DIR})
# set(JPEG_LIBRARY ${JPEG_LIBRARY} ${libjpeg_SOURCE_DIR})

# #freeimage options
# option(ENABLE_TIFF "" OFF)
# option(ENABLE_WEBP "" OFF)
# option(ENABLE_RAW "" OFF)
# option(ENABLE_OPENJP "" OFF)
# option(FREEIMAGE_BUILD_STATIC "" OFF)
# option(FREEIMAGE_BUILD_DLL "" ON)

# #get freeimage
# download_project(PROJ FreeImage
  # GIT_REPOSITORY	  https://github.com/imazen/freeimage.git
  # ${UPDATE_DISCONNECTED_IF_AVAILABLE}
# )



# add_subdirectory(${FreeImage_SOURCE_DIR} ${FreeImage_BINARY_DIR})
# include_directories("${FreeImage_SOURCE_DIR}/Source")

set(assets
  #FreeImage
  #zlib
  #libjpeg
  #libpng
  assimp)

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



set(GLEW_HEADERS
        )


add_dependencies(RaceTheMoon glfw ${glew} ${assets})
target_link_libraries(RaceTheMoon glfw ${glew} ${assets})


