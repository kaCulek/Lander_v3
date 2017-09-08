#include "stdafx.h"
#include "LanderGame.h"
#include "SDL.h"
#include "LanderTexture.h"
#include "TerrainMoon.h"


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
	TerrainMoon terrain = TerrainMoon(renderer);

	//run game
	//Main loop flag
	//Event handler
	bool quit = false;
	SDL_Event e;
	bool moveLanderDown = false;
	int frameTick = 0;

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

		moveLanderDown = frameTick >= 1000;
		if (moveLanderDown)
		{
			lander.MoveDown();
			frameTick = 0;
		}
		lander.RenderCopy();
		terrain.Render();

		SDL_RenderPresent(renderer);

		int landed = terrain.IsIntersected(lander.dstrect);
		if (landed >= 0)
		{
			if (landed == 2)
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
			quit = true;
		}
	}
}


LanderGame::~LanderGame()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}