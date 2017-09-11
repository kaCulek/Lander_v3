// LanderTexture.h : Declarations for the lander
#include "SDL.h"

#pragma once
// Class responsible for creating and moving the lander
class LanderTexture
{
	SDL_Renderer* renderer;  //Lander's rendering state
	SDL_Texture* texture;	//Texture used for creating the lander
	int windowW;	//window width
	int windowH;	//window height
public:
	SDL_Rect dstrect;	//rectangle made from the lander's picture
	LanderTexture(SDL_Renderer* r, SDL_Window *window);		//What creates the Lander (Class constructor)
	void Move(bool moveLeft, bool moveRight, bool moveUp);		//General moving function
	void MoveLeft();		//Moves the lander left
	void MoveRight();		//Moves the lander right
	void MoveUp();		//Moves the lander up
	void MoveDown();		//Moves the lander down
	void RenderCopy();		//Refreshes the lander
	~LanderTexture();		//Class destructor
};