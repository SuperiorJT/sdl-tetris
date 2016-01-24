if("origin/0.1.x" STREQUAL "")
  message(FATAL_ERROR "Tag for git checkout should not be empty.")
endif()

set(run 0)

if("/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitinfo.txt" IS_NEWER_THAN "/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitclone-lastrun.txt")
  set(run 1)
endif()

if(NOT run)
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx'")
endif()

# try the clone 3 times incase there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git" clone "https://github.com/alecthomas/entityx.git" "entityx"
    WORKING_DIRECTORY "/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/alecthomas/entityx.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git" checkout origin/0.1.x
  WORKING_DIRECTORY "/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'origin/0.1.x'")
endif()

execute_process(
  COMMAND "/usr/bin/git" submodule init 
  WORKING_DIRECTORY "/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to init submodules in: '/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx'")
endif()

execute_process(
  COMMAND "/usr/bin/git" submodule update --recursive 
  WORKING_DIRECTORY "/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitinfo.txt"
    "/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitclone-lastrun.txt"
  WORKING_DIRECTORY "/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/Users/justinmiller/Documents/workspace/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitclone-lastrun.txt'")
endif()

