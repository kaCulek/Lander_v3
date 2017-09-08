#include "stdafx.h"
#include "LanderTexture.h"
#include "SDL.h"

LanderTexture::LanderTexture(SDL_Renderer* r, SDL_Window *window)
{
	renderer = r;
	SDL_Surface * image = SDL_LoadBMP("lander.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	dstrect = { 310, 0, 20, 20 };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_RenderPresent(renderer);

	windowW = 0;
	windowH = 0;
	SDL_GetWindowSize(window, &windowW, &windowH);
}

void LanderTexture::Move(bool moveLeft, bool moveRight, bool moveUp)
{
	int moveDownBy = 0;
	int newY = 0;

	if (moveLeft)
	{
		if (dstrect.x > 0)
		{
			dstrect.x = dstrect.x - 10;
		}
	}

	if (moveRight)
	{
		if ((dstrect.x + dstrect.w) < windowW)
		{
			dstrect.x = dstrect.x + 10;
		}
	}

	int gravityFactor = dstrect.y / 20;
	if (gravityFactor >= 20)
	{
		gravityFactor = 20;
	}
	if (gravityFactor < 5)
	{
		gravityFactor = 5;
	}
	moveDownBy = gravityFactor;
	
	if (moveUp)
	{
		moveDownBy = -5;
	}
	
	if (moveDownBy != 0)
	{
		newY = dstrect.y + moveDownBy;
		if (newY >= 0)
		{
			dstrect.y = newY;
		}

		moveDownBy = 0;
	}
}

void LanderTexture::MoveLeft()
{
	Move(true, false, false);
}

void LanderTexture::MoveRight()
{
	Move(false, true, false);
}

void LanderTexture::MoveUp()
{
	Move(false, false, true);
}

void LanderTexture::MoveDown()
{
	Move(false, false, false);
}

void LanderTexture::RenderCopy()
{
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

LanderTexture::~LanderTexture()
{
	SDL_DestroyTexture(texture);
}
