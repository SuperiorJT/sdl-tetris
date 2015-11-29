//
//  game.cpp
//  
//
//  Created by Justin Miller on 11/27/15.
//
//

#include "game.h"
#include "tetris.h"
#include <string>

bool Game::init(Vector2 screenDimens) {
    screen = screenDimens;
    
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
			window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, int(screen.x), int(screen.y), SDL_WINDOW_SHOWN);
			if (window == NULL) {
				printf("Window could not be created! Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (renderer == NULL) {
					printf("Renderer could not be created! Error: %s\n", SDL_GetError());
					success = false;
				}
				else {
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				}
			}
		}
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

    int loops;
    float interpolation;
	Tetris tetris;
	tetris.init();
    SDL_Event e;
    
    while(!quit) {
        loops = 0;
        while (SDL_GetTicks() > next_tick && loops < MAX_FRAMESKIP) {
			printf("Ticks: %u\n", next_tick);

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
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

        interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_tick) / float(SKIP_TICKS);
		tetris.render(interpolation);

		//Render FPS
		SDL_Texture* fpsTexture = renderText("fps: " + std::to_string(fps), "../res/fonts/visitor.ttf", {255, 255, 255, 255}, 18, renderer);
		SDL_RenderCopy(renderer, fpsTexture, NULL, &fpsRenderRect);
		fps_ticks = SDL_GetTicks();

		SDL_RenderPresent(renderer);
    }
    
    //Finish Tetris
    finish();
    
}

void Game::finish() {
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    
	TTF_Quit();
    SDL_Quit();
}