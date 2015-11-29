//
//  GameState.cpp
//
//
//  Created by Justin Miller on 11/27/15.
//
//

#include "tetris_state.h"
#include "tetris.h"

TetrisState::TetrisState()
{
}

void TetrisState::handleInput(Tetris & tetris, SDL_Event e)
{
	switch (e.type) {
	case SDL_MOUSEBUTTONDOWN:
		handleMouseDown(tetris, e);
		break;
	case SDL_MOUSEBUTTONUP:
		handleMouseUp(tetris, e);
		break;
	case SDL_KEYDOWN:
		handleKeyDown(tetris, e);
		break;
	case SDL_KEYUP:
		handleKeyUp(tetris, e);
		break;
	default:
		break;
	}
}

void TetrisState::handleMouseDown(Tetris & tetris, SDL_Event e)
{
	SDL_Log("MouseDown: %i", e.button);
}

void TetrisState::handleMouseUp(Tetris & tetris, SDL_Event e)
{
	SDL_Log("MouseUp: %i", e.button);
}

void TetrisState::handleKeyDown(Tetris & tetris, SDL_Event e)
{
	SDL_Log("KeyDown: %i", e.button);
}

void TetrisState::handleKeyUp(Tetris & tetris, SDL_Event e)
{
	SDL_Log("KeyUp: %i", e.button);
}

void TetrisState::update(Tetris & tetris)
{

}

void MainMenuState::handleMouseDown(Tetris & tetris, SDL_Event e)
{
	TetrisState::handleMouseDown(tetris, e);
}

void MainMenuState::handleMouseUp(Tetris & tetris, SDL_Event e)
{
	TetrisState::handleMouseUp(tetris, e);
}

void MainMenuState::handleKeyDown(Tetris & tetris, SDL_Event e)
{
	TetrisState::handleKeyDown(tetris, e);
}

void MainMenuState::handleKeyUp(Tetris & tetris, SDL_Event e)
{
	TetrisState::handleKeyUp(tetris, e);
}

void MainMenuState::update(Tetris & tetris)
{
	TetrisState::update(tetris);
}
