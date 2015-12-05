project(SDL-Tetris)

include_directories(include Tetris/include core/include)
file(GLOB_RECURSE SOURCES *.cpp *.h)

add_executable(SDL-Tetris ${SOURCES})

target_link_libraries(SDL-Tetris ${ALL_LIBS})

install(TARGETS SDL-Tetris RUNTIME DESTINATION ${BIN_DIR})
