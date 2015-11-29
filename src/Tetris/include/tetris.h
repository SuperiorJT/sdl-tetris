//
//  tetris.h
//  
//
//  Created by Justin Miller on 11/27/15.
//
//

#ifndef ____tetris__
#define ____tetris__

#include <stdio.h>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#undef main
#include <stack>
class TetrisState;
class Tetris {
public:

    Tetris();
    ~Tetris();
    void init();
    void handleInput(SDL_Event e);
    void update();
    void render(float interpolation);
    void finish();

	void pushState(TetrisState* newState);
	void popState();

private:
	std::stack<TetrisState*> state;
};

#endif /* defined(____tetris__) */
