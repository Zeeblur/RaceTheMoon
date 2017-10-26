cmake_minimum_required (VERSION 2.6)
project (RaceTheMoon)

#set c++ standard
set (CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

# add the binary tree to the search path for include files
include_directories ("${PROJECT_BINARY_DIR}")


# Add all files from a src folder
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/components/*.cpp src/components/*.h src/systems/*.cpp src/systems/*.h)

# Add all shaders
file(GLOB_RECURSE SHADER_FILES res/shaders/*.vert res/shaders/*.frag res/shaders/*.geom res/shaders/*.comp)

add_executable(RaceTheMoon ${SOURCES}) 

# add the shaderrrrrrrrrs!
add_custom_command(TARGET RaceTheMoon POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory  "${PROJECT_SOURCE_DIR}/res" $<TARGET_FILE_DIR:RaceTheMoon>/res)

set(GLEW_HEADERS)

# don't download glfw project shit
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_DOCUMENT_INTERNALS "" OFF)
option(GLFW_INSTALL "" OFF)

set(PNG_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(PNG_TESTS OFF CACHE BOOL "" FORCE)
set(PNG_STATIC OFF CACHE BOOL "" FORCE)
set(SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)


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
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(IL_TESTS OFF CACHE BOOL "" FORCE)
set(IL_BUILD_ILUT OFF CACHE BOOL "" FORCE)


#---------------- ASSIMP

#get zlib
add_subdirectory("lib/zlib")
target_include_directories(RaceTheMoon PRIVATE "lib/zlib")
target_include_directories(RaceTheMoon PRIVATE "$(CMAKE_CURRENT_BINARY_DIR)/lib/zlib")

SET(ZLIB_FOUND 1)
#This is for assimp
SET(ZLIB_LIBRARIES zlib)
#This is for libpng
SET(ZLIB_LIBRARY zlib)
SET(ZLIB_INCLUDE_DIR "$(CMAKE_CURRENT_SOURCE_DIR)/lib/zlib")
SET(PNG_BUILD_ZLIB ON CACHE BOOL "" FORCE)

#get glfw
add_subdirectory("lib/glfw")
target_include_directories(RaceTheMoon PRIVATE "lib/glfw/include")

#get glew
            # 896c62c

add_subdirectory("lib/glew")
target_include_directories(RaceTheMoon PRIVATE "lib/glew/include")

## get library for os
GET_DIRECTORY_PROPERTY(glew DIRECTORY "lib/glew" DEFINITION GLEW_NAME)

#get glm
add_subdirectory("lib/glm")
target_include_directories(RaceTheMoon PRIVATE "lib/glm")

#get ASSIMP
add_subdirectory("lib/assimp")
target_include_directories(RaceTheMoon PRIVATE "lib/assimp/include")
target_include_directories(RaceTheMoon PRIVATE "$(CMAKE_CURRENT_BINARY_DIR)/lib/assimp/include")
target_include_directories(assimp PRIVATE "$(CMAKE_CURRENT_BINARY_DIR)/lib/zlib")


#get png
add_subdirectory("lib/libpng")
SET(PNG_INCLUDE_DIRS "lib/libpng" "${CMAKE_CURRENT_BINARY_DIR}/lib/libpng" CACHE PATH "")
target_include_directories(RaceTheMoon PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/lib/libpng")
target_include_directories(png PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/lib/zlib")
target_include_directories(pngfix PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/lib/zlib")
target_include_directories(png-fix-itxt PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/lib/zlib")
SET(PNG_LIBRARIES png CACHE STRING "")
SET(IL_PNG_LIB ON CACHE BOOL "" FORCE)


#get libjpeg
add_subdirectory("lib/libjpeg")
SET(JPEG_INCLUDE_DIRS "lib/libjpeg" "${CMAKE_CURRENT_BINARY_DIR}/lib/libjpeg" CACHE PATH "" FORCE)
target_include_directories(RaceTheMoon PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/lib/libjpeg")
SET(JPEG_LIBRARIES jpeg CACHE STRING "" FORCE)
SET(IL_JPEG_LIB ON CACHE BOOL "" FORCE)

#get devil
add_subdirectory("lib/devil/DevIL")
target_include_directories(RaceTheMoon PRIVATE "lib/devil/DevIL/include")
target_include_directories(IL PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/libpng")
target_include_directories(IL PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/libjpeg")

set(assets
IL
ILU
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


target_link_libraries(RaceTheMoon glfw ${glew} ${assets})
