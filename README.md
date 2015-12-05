# sdl-tetris
Tetris implemented with SDL.

Development Status: Working on EC Structure

## Install Instructions
sdl-tetris is developed cross-platform. Becuase of this, you must build it using [CMake](https://cmake.org/download/).

First of all, you need to install [SDL](https://www.libsdl.org/download-2.0.php), [SDL_TTF](https://www.libsdl.org/projects/SDL_ttf/), and [SDL_IMAGE](https://www.libsdl.org/projects/SDL_image/). If you are on Mac/Linux, all you need to do is install those and run cmake. On Windows, it is a little more complicated:

### Windows Setup

- Create an environment variable called `SDL2` and make the value of it the path to the library root of SDL. After this, merge the SDL_TFF and SDL_IMAGE libraries into that same directory. This is used to find the libraries in cmake.

### Install Cont'd
- Create a folder in the project directory called `build`.
- Run cmake where the build directory is `./build` and source directory is the project root.
- On Mac/Linux, the make files will be generated in the build folder. From there, just run `make && make install` and then run the exe from `../bin`.
- On Windows, generate the build files for Visual Studio (currently 14). From there you can edit the source files and generate a build through the `INSTALL` project. The exe will be placed into the `bin` directory of the project. Due to linking issues with SDL2 and VS14, debug builds are not available on windows. Instead, you have to manually place the dll's from the SDL libraries into the `bin` directory so that the application can run properly.
