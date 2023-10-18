#pragma once
#include <SDL.h>

class HPBar
{
public:
	
	int x, y;
	int hp, hpMax;
	SDL_Renderer* renderer;
	
	HPBar();
	void setup(SDL_Renderer* renderer, int x, int y);
	void draw();


	//~HPBar();

};

