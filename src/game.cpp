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
#include <glm/gtc/type_ptr.hpp>

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
    _cVBO = 0;
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
            -1.0, -1.0,  1.0,
            1.0, -1.0,  1.0,
            1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            // back
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0,
        };
        
        GLfloat colorData[] = {
            // front colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
            // back colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
        };
        
        glGenBuffers(1, &_cVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _cVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
        
        //IBO data
        GLuint indexData[] = {
            // front
            0, 1, 2,
            2, 3, 0,
            // top
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // bottom
            4, 0, 3,
            3, 7, 4,
            // left
            4, 5, 1,
            1, 0, 4,
            // right
            3, 2, 6,
            6, 7, 3,
        };
        
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
        
        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        
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
    
    GLuint MatrixID = glGetUniformLocation(_programID, "mvp");
    
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;
    float testValY = 0.0f;
    float testValX = 0.0f;
    bool projectionMod = false;
    float angle = 0.0f;
    float prevAngle = angle;
    
    glm::mat4 Projection = glm::perspective(glm::radians(90.0f), _screen.x / _screen.y, 0.1f, 100.0f);
    
    glm::mat4 View = glm::lookAt(
                                 glm::vec3(0, 0, 1),
                                 glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0)
                                 );
    
    glm::mat4 Translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    
    glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0));

    glm::mat4 Rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f));
    
    glm::mat4 Model = glm::mat4(1.0f);
    
    glm::mat4 MVP = Projection * View * Model;

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
                if (e.type == SDL_KEYDOWN) {
                    switch( e.key.keysym.sym ) {
                        case SDLK_UP:
                            moveUp = true;
                            break;
                        case SDLK_DOWN:
                            moveDown = true;
                            break;
                        case SDLK_LEFT:
                            moveLeft = true;
                            break;
                        case SDLK_RIGHT:
                            moveRight = true;
                            break;
                        case SDLK_RETURN:
                            projectionMod = !projectionMod;
                        default:
                            break;
                    }
                }
                if (e.type == SDL_KEYUP) {
                    switch( e.key.keysym.sym ) {
                        case SDLK_UP:
                            moveUp = false;
                            break;
                        case SDLK_DOWN:
                            moveDown = false;
                            break;
                        case SDLK_LEFT:
                            moveLeft = false;
                            break;
                        case SDLK_RIGHT:
                            moveRight = false;
                            break;
                        default:
                            break;
                    }
                }
				tetris.handleInput(e);
            }
            
            tetris.update();
            
            if (moveRight) {
                testValX += 0.1f;
            }
            if (moveLeft) {
                testValX -= 0.1f;
            }
            if (moveUp) {
                testValY += 0.1f;
            }
            if (moveDown) {
                testValY -= 0.1f;
            }
            
            prevAngle = angle;
            angle += 0.1f;
            if (angle > 360.f) {
                angle = 0.f;
            }
            
            next_tick += SKIP_TICKS;
            loops++;
        }
        
        interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_tick) / float(SKIP_TICKS);
        
        Projection = glm::perspective(glm::radians(45.0f), _screen.x / _screen.y, 0.1f, 100.0f);
        
        if (projectionMod) {
            Projection = glm::ortho(-10.0f * (_screen.x / _screen.y), 10.0f * (_screen.x / _screen.y), -10.0f, 10.0f, 0.0f, 100.0f);
        }
        
        View = glm::lookAt(
                           glm::vec3(0, 0, 4),
                           glm::vec3(0, 0, 0),
                           glm::vec3(0, 1, 0)
                           );
        
        Translate = glm::translate(glm::mat4(1.0f), glm::vec3(testValX, testValY, 0.0f));
        
        Scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5));
        
        Rotate = glm::rotate(glm::mat4(1.0f), glm::mix(prevAngle, angle, interpolation), glm::vec3(1.0f, 1.0f, 0.0f));
        
        Model = Translate * Rotate * Scale;
        
        MVP = Projection * View * Model;

		//Clear the screen
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(_programID);
        
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
        
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glEnableVertexAttribArray(_vertexPos2DLocation);
        glVertexAttribPointer(_vertexPos2DLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, _cVBO);
        glEnableVertexAttribArray(_vertexColor);
        glVertexAttribPointer(_vertexColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
        
        glDisableVertexAttribArray(_vertexPos2DLocation);
        glDisableVertexAttribArray(_vertexColor);
        
        glUseProgram(NULL);

        
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
