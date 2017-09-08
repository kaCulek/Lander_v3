#include "stdafx.h"
#include "TerrainMoon.h"
#include "SDL.h"
#include <vector>

TerrainMoon::TerrainMoon(SDL_Renderer* r)
{
	renderer = r;
}

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
		{ 300, 450 },
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
		{ 300, 450 },
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
		if (SDL_IntersectRectAndLine(&rect, &x1.x, &x1.y, &x2.x, &x2.y))
		{
			if (x1.y == x2.y)
			{
				//has landed successfuly
				result = 2;
			}
			else
			{
				//landed but not successfuly
				result = 1;
			}
			break;
		}
	}
	return result;
}

TerrainMoon::~TerrainMoon()
{
}
