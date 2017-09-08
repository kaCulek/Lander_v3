#include "SDL.h"

#pragma once
class LanderTexture
{
	SDL_Renderer* renderer;
	
	SDL_Texture * texture;
	int windowW;
	int windowH;

public:
	SDL_Rect dstrect;
	LanderTexture(SDL_Renderer* r, SDL_Window *window);
	void Move(bool moveLeft, bool moveRight, bool moveUp);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void RenderCopy();
	~LanderTexture();
};

