//
//  game.cpp
//  
//
//  Created by Justin Miller on 11/27/15.
//
//

#include "game.h"

bool Game::init(Vector2 screenDimens) {
    screen = screenDimens;
    
    bool success = true;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL! Error: %s\n", SDL_GetError());
        success = false;
    } else {
        window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.x, screen.y, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! Error: %s\n", SDL_GetError());
            success = false;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Renderer could not be created! Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }
        }
    }
    
    return success;
}

void Game::start(const int TICKS_PER_SECOND, const int MAX_FRAMESKIP) {
    
    bool quit = false;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    float next_tick = SDL_GetTicks();
    int loops;
    float interpolation;
    //Init Tetris
    SDL_Event e;
    
    while(!quit) {
        loops = 0;
        while (SDL_GetTicks() > next_tick && loops < MAX_FRAMESKIP) {
            while(SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                //Tetris Handle Input
                //Tetris Update
            }
            next_tick += SKIP_TICKS;
            loops++;
        }
        
        interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_tick) / float(SKIP_TICKS);
        //Tetris Render
        
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