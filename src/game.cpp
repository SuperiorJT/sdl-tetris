//
//  game.cpp
//
//
//  Created by Justin Miller on 11/27/15.
//
//

#include "game.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "tetris.h"

Game::Game(Vector2 screenDimens) {
    Game::init(screenDimens);
}

Game::~Game() {
    Game::finish();
}

void Game::init(Vector2 screenDimens) {
    _screen = screenDimens;
    _programID = 0;
    _vertexPos2DLocation = -1;
    _vertexColor = -1;
    _VBO = 0;
    _IBO = 0;

    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL! Error: %s\n", SDL_GetError());
        success = false;
    } else {
		if (TTF_Init() != 0) {
			printf("Could not initialize TTF! Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
            SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
            SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
            SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
            
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

			_window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, int(_screen.x), int(_screen.y), SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
			if (_window == NULL) {
				printf("Window could not be created! Error: %s\n", SDL_GetError());
				success = false;
            } else {
                _glContext = SDL_GL_CreateContext(_window);
                
                if (_glContext == NULL) {
                    printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
                    success = false;
                } else {
                    //Initialize GLEW
                    glewExperimental = GL_TRUE;
                    GLenum glewError = glewInit();
                    glGetError();
                    if( glewError != GLEW_OK )
                    {
                        printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
                    }
                    if (SDL_GL_SetSwapInterval(1) < 0) {
                        printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
                    }
                    if( !Game::initGL() )
                    {
                        printf( "Unable to initialize OpenGL!\n" );
                        success = false;
                    }
                }
            }
		}
    }
    if (!success) {
        exit(1);
    }
}

bool Game::initGL() {
    bool success = true;
    
    _programID = LoadShaders("../res/shaders/simpleVertex.vs", "../res/shaders/simpleFragment.fs");
    
    _vertexPos2DLocation = glGetAttribLocation(_programID, "position");
    _vertexColor = glGetAttribLocation(_programID, "color");
    if (_vertexPos2DLocation == -1) {
        printf( "position is not a valid glsl program variable!\n" );
        success = false;
    } else {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        
        //VBO data
        GLfloat vertexData[] = {
            -0.5f, -0.5f, 1.0, 0.0, 0.0,
            0.5f, -0.5f, 0.0, 1.0, 0.0,
            0.5f,  0.5f, 0.0, 0.0, 1.0,
            -0.5f,  0.5f, 1.0, 1.0, 1.0
        };
        
        //IBO data
        GLuint indexData[] = {0, 1, 2, 3};
        
        //Create VBO
        glGenBuffers(1, &_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        
        //Create IBO
        glGenBuffers(1, &_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
        
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
    }
    
    return success;
}

void Game::start(const int TICKS_PER_SECOND, const int MAX_FRAMESKIP) {

    bool quit = false;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    Uint32 next_tick = SDL_GetTicks();

	Uint32 fps_ticks = SDL_GetTicks();
	Uint32 fps = 0;
	SDL_Rect fpsRenderRect = { 10, 10, 50, 30 };
    SDL_Color fpsColor = {255, 255, 255, 255};

    int loops;
    float interpolation;
	Tetris tetris;
	tetris.init();
    SDL_Event e;

    while(!quit) {
        loops = 0;
        while (SDL_GetTicks() > next_tick && loops < MAX_FRAMESKIP) {

			if (SDL_GetTicks() > fps_ticks) {
				float fps_delta = (SDL_GetTicks() - fps_ticks) / 1000.0f;
				fps = Uint32(1.0 / fps_delta);
			}

            while(SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
				tetris.handleInput(e);
				tetris.update();
            }
            next_tick += SKIP_TICKS;
            loops++;
        }

		//Clear the screen
        glClear ( GL_COLOR_BUFFER_BIT );
        
        glUseProgram(_programID);
        
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glEnableVertexAttribArray(_vertexPos2DLocation);
        glVertexAttribPointer(_vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(_vertexColor);
        glVertexAttribPointer(_vertexColor, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
        
        glDisableVertexAttribArray(_vertexPos2DLocation);
        glDisableVertexAttribArray(_vertexColor);
        
        glUseProgram(NULL);

        interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_tick) / float(SKIP_TICKS);
		tetris.render(interpolation);

		//Render FPS

		fps_ticks = SDL_GetTicks();

        SDL_GL_SwapWindow(_window);
    }

}

void Game::finish() {
    glDeleteProgram(_programID);
    SDL_GL_DeleteContext(_glContext);
    SDL_DestroyWindow(_window);
    _glContext = NULL;
    _window = NULL;

	TTF_Quit();
    SDL_Quit();
}
