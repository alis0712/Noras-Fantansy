#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;


class InfoBox
{
public:
	SDL_Renderer* renderer;

	TTF_Font* font;

	string text;
	SDL_Texture* textTexture = NULL;
	SDL_Rect textRect;
	SDL_Rect boxRect;

	bool visible = true;

	InfoBox();
	~InfoBox();

	void setup(SDL_Renderer* renderer);
	void setText(string text);
	void draw();

};

