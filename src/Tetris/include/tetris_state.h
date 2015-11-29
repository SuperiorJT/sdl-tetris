//
//  GameState.h
//
//
//  Created by Justin Miller on 11/27/15.
//
//

#ifndef ____tetris_state__
#define ____tetris_state__

#include <stdio.h>
#ifdef _WIN32
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif
#undef main
class Tetris;
class TetrisState {

public:
	TetrisState();
	virtual ~TetrisState() {};
	void handleInput(Tetris& tetris, SDL_Event e);
	virtual void handleMouseDown(Tetris & tetris, SDL_Event e);
	virtual void handleMouseUp(Tetris & tetris, SDL_Event e);
	virtual void handleKeyDown(Tetris & tetris, SDL_Event e);
	virtual void handleKeyUp(Tetris & tetris, SDL_Event e);
    virtual void update(Tetris& tetris);
};

class MainMenuState : public TetrisState {
public:
	void handleMouseDown(Tetris & tetris, SDL_Event e);
	void handleMouseUp(Tetris & tetris, SDL_Event e);
	void handleKeyDown(Tetris & tetris, SDL_Event e);
	void handleKeyUp(Tetris & tetris, SDL_Event e);
    void update(Tetris& tetris);
};

class SettingsState : public TetrisState {
public:
	void handleMouseDown(Tetris & tetris, SDL_Event e);
	void handleMouseUp(Tetris & tetris, SDL_Event e);
	void handleKeyDown(Tetris & tetris, SDL_Event e);
	void handleKeyUp(Tetris & tetris, SDL_Event e);
	void update(Tetris& tetris);
};

class PlayingState : public TetrisState {
public:
	void handleMouseDown(Tetris & tetris, SDL_Event e);
	void handleMouseUp(Tetris & tetris, SDL_Event e);
	void handleKeyDown(Tetris & tetris, SDL_Event e);
	void handleKeyUp(Tetris & tetris, SDL_Event e);
	void update(Tetris& tetris);
};

class PausedState : public TetrisState {
public:
	void handleMouseDown(Tetris & tetris, SDL_Event e);
	void handleMouseUp(Tetris & tetris, SDL_Event e);
	void handleKeyDown(Tetris & tetris, SDL_Event e);
	void handleKeyUp(Tetris & tetris, SDL_Event e);
	void update(Tetris& tetris);
};

class LoadingState : public TetrisState {
public:
	void handleMouseDown(Tetris & tetris, SDL_Event e);
	void handleMouseUp(Tetris & tetris, SDL_Event e);
	void handleKeyDown(Tetris & tetris, SDL_Event e);
	void handleKeyUp(Tetris & tetris, SDL_Event e);
	void update(Tetris& tetris);
};

#endif /* defined(____tetris_state__) */
