project(SDL-Tetris)

include_directories(include Tetris/include)
file(GLOB_RECURSE SOURCES *.cpp *.h)

add_executable(SDL-Tetris ${SOURCES})

target_link_libraries(SDL-Tetris ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})

install(TARGETS SDL-Tetris RUNTIME DESTINATION ${BIN_DIR})
