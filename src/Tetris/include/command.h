#pragma once

#include <stdio.h>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#undef main

#include <tetris.h>

class Command {
public:
	SDL_Keycode key;
	virtual ~Command() {};
	virtual void execute() {};
};

class StartGameCommand : public Command {
public:
	SDL_Keycode key = SDLK_RETURN;
	virtual void execute(Tetris tetris);
};