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
	Command() {};
	virtual ~Command() {};
	virtual void execute() {};
};

class StartGameCommand : public Command {
public:
	StartGameCommand();
	virtual void execute(Tetris tetris);
};
