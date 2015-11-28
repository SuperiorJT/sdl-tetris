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
#include <SDL2/SDL.h>
#include "math.h"

class Game {
    
public:
    Vector2 screen;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    Game() {};
    ~Game() {};
    bool init(Vector2 screenDimens);
    void start(const int TICKS_PER_SECOND = 25, int MAX_FRAMESKIP = 5);
    void finish();
    
};

#endif /* defined(____game__) */
