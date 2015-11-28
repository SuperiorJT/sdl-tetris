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

class Tetris {
    enum GameState {
        MENU, SETTINGS, PAUSED, PLAYING
    };
public:
    Tetris();
    ~Tetris();
    void init();
    void handleInput();
    void update();
    void render(float interpolation);
    void finish();
};

#endif /* defined(____tetris__) */
