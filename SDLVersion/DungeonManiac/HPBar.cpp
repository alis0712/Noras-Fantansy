#include "HPBar.h"

HPBar::HPBar()
{
	// default hp
	hp = hpMax = 100; // right to left in equal signs
}

void HPBar::setup(SDL_Renderer* renderer, int x, int y)
{
	this->renderer = renderer;
	this->x = x;
	this->y = y;

}

void HPBar::draw()
{
	SDL_Rect back = { x, y, 102, 12 }; // x, y, w, h
	// draw white part of bar
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &back);
	
	// draw black border

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &back);

	float hpF = hp; // so that we don't get stuck with integer division


	int hpBarWidth = (hpF / hpMax) * 100; // 100 is width of pixels of full health bar

	if (hpBarWidth < 0)
	{
		hpBarWidth = 0;
	}

	SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);

	SDL_Rect hpColorBar = { x + 1, y + 1, hpBarWidth, 10 }; // x, y, w, h

	SDL_RenderFillRect(renderer, &hpColorBar);





	// white bgd

	// 
}
