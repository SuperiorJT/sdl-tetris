//
//  game.cpp
//  
//
//  Created by Justin Miller on 11/27/15.
//
//

#include "game.h"
#include "tetris.h"

bool Game::init(Vector2 screenDimens) {
    screen = screenDimens;
    
    bool success = true;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL! Error: %s\n", SDL_GetError());
        success = false;
    } else {
        window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, int(screen.x), int(screen.y), SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! Error: %s\n", SDL_GetError());
            success = false;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Renderer could not be created! Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
        }
    }
    return success;
}

void Game::start(const int TICKS_PER_SECOND, const int MAX_FRAMESKIP) {
    
    bool quit = false;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    Uint32 next_tick = SDL_GetTicks();
    int loops;
    float interpolation;
	Tetris tetris;
	tetris.init();
    SDL_Event e;
    
    while(!quit) {
        loops = 0;
        while (SDL_GetTicks() > next_tick && loops < MAX_FRAMESKIP) {
			printf("Ticks: %u\n", next_tick);
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
    
    SDL_Quit();
}