//LanderGame.h : Declaration of the main game window
#include "SDL.h"

#pragma once
class LanderGame
{
	SDL_Window *window;		//main game window
	SDL_Renderer* renderer;		//window's rendering
public:
	LanderGame();
	void Start();		//starts a new game instance
	~LanderGame();
};

