#include "SDL.h"

#pragma once

class TerrainMoon
{
	SDL_Renderer* renderer;

public:

	TerrainMoon(SDL_Renderer* r);
	int IsIntersected(SDL_Rect rect);
	void Render();
	~TerrainMoon();
};

