//
//  game.h
//
//
//  Created by Justin Miller on 11/27/15.
//
//

#ifndef ____game__
#define ____game__

#include <stdio.h>
#include <string>
#include "GL/glew.h"
#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_ttf.h>
	#include <SDL_opengl.h>
	#undef main
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_opengl.h>
#endif
#include "utility.h"

class Game {

public:
    Game(Vector2 screenDimens);
    ~Game();
    void start(const int TICKS_PER_SECOND = 25, int MAX_FRAMESKIP = 5);
private:
	Vector2 _screen;
    SDL_Window* _window;
	SDL_GLContext _glContext;
    GLuint _programID;
    GLint _vertexPos2DLocation;
    GLint _vertexColor;
    GLuint _VBO;
    GLuint _IBO;

	void init(Vector2 screenDimens);
    bool initGL();
	void finish();
};

#endif /* defined(____game__) */
