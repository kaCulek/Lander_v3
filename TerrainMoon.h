// TerrainMoon.h : Declarations for the moon surface
#include "SDL.h"

#pragma once
//Class responsible for creating the moon surface
class TerrainMoon
{
	SDL_Renderer* renderer;		//Surface's rendering state
public:
	TerrainMoon(SDL_Renderer* r);		//Class constructor
	int IsIntersected(SDL_Rect rect);		//Checks whether or not lander has landed
	void Render();		//Draws the moon surface
	~TerrainMoon();		//Class destructor
};