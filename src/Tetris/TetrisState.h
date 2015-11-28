//
//  GameState.h
//
//
//  Created by Justin Miller on 11/27/15.
//
//

#ifndef ____TetrisState__
#define ____TetrisState__

#include <stdio.h>
#ifdef _WIN32
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif
#undef main
#include "tetris.h"

class TetrisState {

public:
    virtual ~TetrisState();
    virtual void handleInput(Tetris& tetris, SDL_Event e);
    virtual void update();
};

class MainMenuState : public TetrisState {
public:
    virtual void handleInput(Tetris& tetris, SDL_Event e);
    virtual void update();
};

#endif /* defined(____TetrisState__) */
