cmake_minimum_required (VERSION 2.6)
project (SDL-Tetris)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SDL-Tetris_SOURCE_DIR}/cmake")
# Set an output directory for our binaries
set(BIN_DIR ${SDL-Tetris_SOURCE_DIR}/bin)


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

add_subdirectory(src)
