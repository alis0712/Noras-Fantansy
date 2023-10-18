#include "BattleButton.h"

BattleButton::~BattleButton()
{
	if (textTexture != NULL)
	{
		SDL_DestroyTexture(textTexture);
	}

}

void BattleButton::setup(SDL_Renderer* renderer, SDL_Rect buttonRect, string text)
{
	this->renderer = renderer;
	this->buttonRect = buttonRect;


	//Create Name Texture
	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
	SDL_Color textColor = { 0,0,0,0 };
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);

	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	//setup name texture drawing destination rectangle
	textRect.x = buttonRect.x + 2; // + 2 is added for padding
	textRect.y = buttonRect.y + 2; // + 2 is added for padding
	
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	selected = false;

}

void BattleButton::draw()
{
	// use different render color for buttons if selected or not

	if (selected)
	{
		SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
	}

	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}

	// render button background
	SDL_RenderFillRect(renderer, &buttonRect);

	// render border
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &buttonRect);

	// render button text to screen
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);


}

void BattleButton::drawInactive()
{
	
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	

	/*else
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}*/

	// render button background
	SDL_RenderFillRect(renderer, &buttonRect);

	// render border
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &buttonRect);

	// render button text to screen
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}
