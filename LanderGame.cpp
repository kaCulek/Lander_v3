#include "stdafx.h"
#include "LanderGame.h"
#include "SDL.h"
#include <vector>
#include "LanderTexture.h"

#define POINTS_COUNT 15

static SDL_Point points[POINTS_COUNT] = {
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


LanderGame::LanderGame()
{
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"Lunar Lander",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               // width, in pixels
		480,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	// Check that the window was successfully created
	if (window != NULL) {
		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_RenderClear(renderer);
	}
}

void LanderGame::Start()
{
	if (window == NULL || renderer == NULL)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error",
			"No window found",
			NULL);
		return;
	}

	//Add lander
	LanderTexture lander = LanderTexture(renderer, window);

	//run game
	//Main loop flag
	//Event handler
	bool quit = false;

	SDL_Event e;
	bool moveLanderDown = false;
	int frameTick = 0;
	bool hasLanded = false;
	bool hasLandedSuccessfully = false;

	while (!quit)
	{
		frameTick++;
		
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_LEFT){
					lander.MoveLeft();
				}
				if (e.key.keysym.sym == SDLK_RIGHT){
					lander.MoveRight();
				}
				if (e.key.keysym.sym == SDLK_UP){
					lander.MoveUp();
				}
			}
		}

		SDL_RenderClear(renderer);
		
		/*if ((dstrect.y + dstrect.h) >= windowH)
		{
			quit = true;
		}*/

		for (int i = 0; i < (POINTS_COUNT - 1); i++)
		{
			SDL_Point x1 = points[i];
			SDL_Point x2 = points[i + 1];
			hasLanded = SDL_IntersectRectAndLine(&lander.dstrect, &x1.x, &x1.y, &x2.x, &x2.y);
			if (hasLanded)
			{
				hasLandedSuccessfully = x1.y == x2.y;
				break;
			}
		}
		if (hasLanded)
		{
			quit = true;
		}

		moveLanderDown = frameTick >= 1000;
		if (moveLanderDown)
		{
			lander.MoveDown();
			frameTick = 0;
		}
		lander.RenderCopy();
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		SDL_RenderPresent(renderer);
	}

	if (hasLandedSuccessfully)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
			"Landing Successful.",
			"You landed successfully.",
			NULL);
	}
	else
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
			"Landing Failed.",
			"You have created a two mile crater.",
			NULL);
	}

	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


LanderGame::~LanderGame()
{
}


