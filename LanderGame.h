#include "SDL.h"

#pragma once
class LanderGame
{
	SDL_Window *window;
	SDL_Renderer* renderer;
public:
	LanderGame();
	void Start();
	~LanderGame();
};

