// TerrainMoon.cpp : Creating and working with the moon surface
#include "stdafx.h"
#include "TerrainMoon.h"
#include "SDL.h"
//Class constructor
TerrainMoon::TerrainMoon(SDL_Renderer* r)
{
	renderer = r;
}
//  FUNCTION: Render()
//  PURPOSE: Defines and draws the moon surface
void TerrainMoon::Render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_Point points[15] = {
		{ 0, 480 },
		{ 50, 450 },
		{ 100, 400 },
		{ 125, 400 },
		{ 150, 350 },
		{ 200, 400 },
		{ 250, 450 },
		{ 320, 450 },
		{ 350, 400 },
		{ 400, 400 },
		{ 450, 300 },
		{ 500, 250 },
		{ 550, 300 },
		{ 600, 300 },
		{ 640, 480 }
	};
	SDL_RenderDrawLines(renderer, points, 15);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}
//  FUNCTION: IsIntersected(SDL_Rect rect)
//  PURPOSE: Checks if the lander has landed on the surface for every segment
int TerrainMoon::IsIntersected(SDL_Rect rect)
{
	int result = -1;
	SDL_Point points[15] = {
		{ 0, 480 },
		{ 50, 450 },
		{ 100, 400 },
		{ 125, 400 },
		{ 150, 350 },
		{ 200, 400 },
		{ 250, 450 },
		{ 320, 450 },
		{ 350, 400 },
		{ 400, 400 },
		{ 450, 300 },
		{ 500, 250 },
		{ 550, 300 },
		{ 600, 300 },
		{ 640, 480 }
	};
	for (int i = 0; i < (15 - 1); i++)
	{
		SDL_Point x1 = points[i];
		SDL_Point x2 = points[i + 1];
		//checks for successful/unsuccessful landing
		if (SDL_IntersectRectAndLine(&rect, &x1.x, &x1.y, &x2.x, &x2.y))
		{
			if (x1.y == x2.y)
			{
				//has landed successfully
				result = 2;
			}
			else
			{
				//landed but not successfully
				result = 1;
			}
			break;
		}
	}
	return result;
}
//Class destructor
TerrainMoon::~TerrainMoon()
{
}