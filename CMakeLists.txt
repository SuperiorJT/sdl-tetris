cmake_minimum_required (VERSION 3.4.0)
project (SDL-Tetris)
include(ExternalProject)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SDL-Tetris_SOURCE_DIR}/cmake")
# Set an output directory for our binaries
set(BIN_DIR ${SDL-Tetris_SOURCE_DIR}/bin)

find_package(OpenGL REQUIRED)

if (WIN32)
    ADD_DEFINITIONS( -DGLEW_STATIC )
    add_library(GLEW_1130 STATIC IMPORTED)
    set_target_properties(GLEW_1130 PROPERTIES IMPORTED_LOCATION ${SDL-Tetris_SOURCE_DIR}/libs/glew-1.13.0/lib/glew32s.lib)
else(WIN32)
    add_subdirectory(libs)
endif(WIN32)

include_directories(
    libs/glew-1.13.0/include
    libs/glm-0.9.7.1/
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

set(entityx_DIR "${SDL-Tetris_SOURCE_DIR}/libs/entityx-1.1.2")
# Later should handle multiple possible build configurations per:
# https://stackoverflow.com/questions/6351609/cmake-linking-to-library-downloaded-from-externalproject-add
set(entityx_LIBRARY "${entityx_DIR}/lib/libentityx.a")
set(entityx_INCLUDE_DIR "${entityx_DIR}/include")
ExternalProject_Add(entityx
	PREFIX ${entityx_DIR}
	GIT_REPOSITORY https://github.com/alecthomas/entityx.git
	GIT_TAG origin/0.1.x
	INSTALL_DIR ${entityx_DIR}
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${entityx_DIR}
)
include_directories(${entityx_DIR})

# Bump up warning levels appropriately for each compiler
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -ggdb -std=c++11")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /Zi")
	endif()
endif()

set(ALL_LIBS
    ${SDL2_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${OPENGL_LIBRARY}
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    GLEW_1130
)

add_subdirectory(src)
