if("origin/0.1.x" STREQUAL "")
  message(FATAL_ERROR "Tag for git checkout should not be empty.")
endif()

set(run 0)

if("D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitinfo.txt" IS_NEWER_THAN "D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitclone-lastrun.txt")
  set(run 1)
endif()

if(NOT run)
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx'")
endif()

# try the clone 3 times incase there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "D:/Git/cmd/git.exe" clone "https://github.com/alecthomas/entityx.git" "entityx"
    WORKING_DIRECTORY "D:/Repos/sdl-tetris/libs/entityx-1.1.2/src"
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
  COMMAND "D:/Git/cmd/git.exe" checkout origin/0.1.x
  WORKING_DIRECTORY "D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'origin/0.1.x'")
endif()

execute_process(
  COMMAND "D:/Git/cmd/git.exe" submodule init 
  WORKING_DIRECTORY "D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to init submodules in: 'D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx'")
endif()

execute_process(
  COMMAND "D:/Git/cmd/git.exe" submodule update --recursive 
  WORKING_DIRECTORY "D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitinfo.txt"
    "D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitclone-lastrun.txt"
  WORKING_DIRECTORY "D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'D:/Repos/sdl-tetris/libs/entityx-1.1.2/src/entityx-stamp/entityx-gitclone-lastrun.txt'")
endif()

