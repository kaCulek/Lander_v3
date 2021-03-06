//LanderGame.cpp : The main game window
#include "stdafx.h"
//Class constructor
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
		SDL_WINDOW_OPENGL				// flags - see below, SDL_WINDOW_INPUT_GRABBED DOESN'T WORK (KEYBOARD OVERRIDE D:)
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
		// if the window was NOT successfully created
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error",
			"No window found.",
			NULL);
		return;
	}
	//Add lander
	LanderTexture lander = LanderTexture(renderer, window);
	//Add surface
	TerrainMoon terrain = TerrainMoon(renderer);
	//run game
	//Main loop flag
	bool quit = false;
	bool isMinimized = false;
	//Event handler
	SDL_Event e;
	bool moveLanderDown = false;
	int frameTick = 0;
	//Run until quitting or the game has ended
	while (!quit)
	{
		frameTick++;
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_WINDOWEVENT)
			{
				if (e.window.event == SDL_WINDOWEVENT_MINIMIZED)
				{
					isMinimized = true;
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
						"Game Paused",
						"Press OK to continue.",
						NULL);
					SDL_RestoreWindow(window);
					SDL_Delay(3000);
				}
				if (e.window.event == SDL_WINDOWEVENT_RESTORED)
				{
					isMinimized = false;
				}
			} 
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			//Key bindings for moving the lander
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
		//Lander moving on its own (gravity)
		moveLanderDown = (frameTick >= 1000);
		if (moveLanderDown)
		{
			lander.MoveDown();
			frameTick = 0;
		}
		//Checking if lander has landed
		lander.RenderCopy();
		terrain.Render();
		SDL_RenderPresent(renderer);
		int landed = terrain.IsIntersected(lander.dstrect);
		if (landed >= 0)
		{
			//landing successful
			if (landed == 2)
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
					"Landing Successful.",
					"You landed successfully.",
					NULL);
			}
			//landing unsuccessful
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
//Class destructor
LanderGame::~LanderGame()
{
	//destroys all windows/instances and exits the window
	SDL_DestroyRenderer(renderer); 
	SDL_DestroyWindow(window);
	SDL_Quit();
}