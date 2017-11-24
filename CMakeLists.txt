cmake_minimum_required(VERSION 3.9)
# Compiler flags
if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
endif(MSVC)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#====================================================================

project(RaceTheMoon)

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/bin")
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
# Add all shaders
file(GLOB_RECURSE SHADER_FILES res/shaders/*.vert res/shaders/*.frag res/shaders/*.geom res/shaders/*.comp)
add_executable(RaceTheMoon ${SOURCE_FILES} ${SHADER_FILES} src/thread_pool.cpp src/thread_pool.h)

add_custom_target(
	copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory  "${PROJECT_SOURCE_DIR}/res" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/res"
)

#====================================================================

#GLEW options
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(GLEW_HEADERS)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(GLEW_HEADERS)
else()
	option(BUILD_UTILS "" OFF)
	option(BUILD_SHARED_LIBS "" ON)
	option(glew-cmake_BUILD_MULTI_CONTEXT "" OFF)
	option(glew-cmake_BUILD_SHARED "" ON)
	option(glew-cmake_BUILD_SINGLE_CONTEXT "" ON)
	option(glew-cmake_BUILD_STATIC "" OFF)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#GLFW options
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_DOCUMENT_INTERNALS "" OFF)
option(GLFW_INSTALL "" OFF)
#GLM options
option(GLM_DYNAMIC_LIBRARY_ENABLE "" OFF)
option(GLM_TEST_ENABLE_FAST_MATH "" ON)
option(GLM_TEST_ENABLE_LANG_EXTENSIONS "" ON)
option(GLM_TEST_ENABLE_SIMD_AVX2 "" ON)
option(GLM_TEST_ENABLE_SIMD_SSE3 "" ON)
#ASSIMP
option(ASSIMP_BUILD_ASSIMP_TOOLS "" OFF)
option(ASSIMP_BUILD_TESTS "" OFF)
set(LIBRARY_SUFFIX "" CACHE STRING "the suffix for the assimp windows library")
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

#TODO: go back and enable this, submit bug report
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
set(BuildTests OFF CACHE BOOL "" FORCE)
#SFML
set(SFML_BUILD_WINDOW OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_GRAPHICS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO ON CACHE BOOL "" FORCE)
#set(SFML_BUILD_FRAMEWORKS ON CACHE BOOL "" FORCE)
#set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
#set(DESTINATION CMAKE_LIBRARY_OUTPUT_DIRECTORY)
#set(PREDEFINED_TARGETS_FOLDER "CMake")
MESSAGE( STATUS "==========xd============" )
#================================================
# GLFW https://github.com/glfw/glfw.git 56ecd62f
add_subdirectory("lib/glfw")
target_include_directories(RaceTheMoon PUBLIC "lib/glfw/include/")
#================================================
# GLM https://github.com/g-truc/glm.git 77332664
add_subdirectory("lib/glm")
target_include_directories(RaceTheMoon PUBLIC "lib/glm")
#================================================
# assimp https://github.com/assimp/assimp 114c48b
add_subdirectory("lib/assimp")
target_include_directories(RaceTheMoon PUBLIC "lib/assimp/include")
target_include_directories(RaceTheMoon PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/lib/assimp/include")
target_include_directories(assimp PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/lib/zlib")
#================================================
# sfml https://github.com/SFML/SFML 013d053 
add_subdirectory("lib/sfml")
target_include_directories(RaceTheMoon PUBLIC "lib/sfml/include")
#target_include_directories(SFML PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/lib/sfml")
install(TARGETS RaceTheMoon DESTINATION lib)
#================================================
# OpenGL
FIND_PACKAGE( OpenGL REQUIRED)
if(NOT ${OPENGL_FOUND})
  message(FATAL_ERROR "OPENGL NOT FOUND")
endif()
#====================================================================
# GLEW
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	add_definitions(-DGLEW_STATIC)
	# GLEW https://github.com/menpo/glew.git
	add_subdirectory("lib/glew")
	target_include_directories(RaceTheMoon PUBLIC "lib/glew/include")
	## get library for os
	GET_DIRECTORY_PROPERTY(GLEWLIB DIRECTORY "lib/glew" DEFINITION GLEW_NAME)

    set(GLEWLIB
            ${OPENGL_LIBRARIES}
            -lGL -lGLU -lXrandr -lXext -lX11 -lrt
            ${CMAKE_DL_LIBS}
	    glm
		 ${GLEWLIB}
         )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(GLEWLIB
            ${OPENGL_LIBRARIES}
            ${CMAKE_DL_LIBS}
	    glm
			${GLEWLIB}
		)
else()
	# GLEW https://github.com/Perlmint/glew-cmake.git ea68a21
	add_subdirectory("lib/glew_windows")
	target_include_directories(RaceTheMoon PUBLIC "lib/glew_windows/include")
	set(GLEWLIB libglew_shared)
    set_target_properties(${GLEWLIB} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
            )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#====================================================================



#====================================================================

target_link_libraries(RaceTheMoon 
	PUBLIC ${GLEWLIB}
	PUBLIC glfw
	PUBLIC assimp
	PUBLIC sfml-audio
	#optimized sfml-audio debug sfml-audio-d 
)
add_dependencies(RaceTheMoon
	copy_resources
)

#====================================================================

set(deps glfw assimp ${GLEWLIB} sfml-audio)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
else()
	set(junk 
		glm_dummy 
		UpdateAssimpLibsDebugSymbolsAndDLLs 
	)
	FOREACH(jnk ${junk})
		#Hide junks in junk VS project folder
		set_target_properties(${jnk} PROPERTIES FOLDER "JUNK")
	ENDFOREACH()
endif()

FOREACH(dep ${deps})
	#Hide deps in dep VS project folder

	if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	else()
        set_target_properties(${dep} PROPERTIES FOLDER "DEPS")
		#Disable warnings for deps
		target_compile_options(${dep} PUBLIC "/W0")
		#use all core compilation
		target_compile_options(${dep} PUBLIC "/MP")
	endif()
ENDFOREACH()

if(${ENU_GFX_TEST})
	add_custom_command(TARGET framework_test POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/res"
		"$<TARGET_FILE_DIR:framework_test>"
	)

	FOREACH(dep ${deps})
		add_custom_command(TARGET framework_test POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:${dep}>
			$<TARGET_FILE_DIR:framework_test>
		)
	ENDFOREACH()
endif()

