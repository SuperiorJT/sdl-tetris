//
//  tetris.cpp
//  
//
//  Created by Justin Miller on 11/27/15.
//
//

#include "tetris.h"
#include "tetris_state.h"

Tetris::Tetris()
{
}

Tetris::~Tetris()
{
}

void Tetris::init()
{
	state.push(new MainMenuState());
}

void Tetris::handleInput(SDL_Event e)
{
	state.top()->handleInput(*this, e);
}

void Tetris::update()
{
	state.top()->update(*this);
}

void Tetris::render(float interpolation)
{
	//Render GameObjects
	//Render UI Objects
}

void Tetris::finish()
{
	//Destroy All Entities
}

void Tetris::pushState(TetrisState* newState)
{
	state.push(newState);
}

void Tetris::popState()
{
	state.pop();
}
