//
//  main.cpp
//  SDL-Tetris
//
//  Created by Justin Miller on 11/27/15.
//  Copyright (c) 2015 Justin Miller. All rights reserved.
//

#include <iostream>
#include "game.h"

int main(int argc, const char * argv[]) {
    Vector2 screen = Vector2(640, 480);
    Game* game = new Game(screen);
    game->start();
    return 0;
}
