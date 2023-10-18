#include "Animation.h"

void Animation::setup(string spriteSheetFile, SDL_Renderer* renderer, int numberOfFrames, float frameDuration, int offsetX, int offsetY)
{
	this->renderer = renderer;
	this->spriteSheet = IMG_LoadTexture(renderer, spriteSheetFile.c_str());

	// temp variables to hold texture width and height

	int w, h;

	SDL_QueryTexture(spriteSheet, NULL, NULL, &w, &h);

	// can calcualate frame width and frame height now
	frameWidth = w / numberOfFrames;
	frameHeight = h;

	this->numberOfFrames = numberOfFrames;
	this->frameDuration = frameDuration;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

Animation::~Animation()
{
	if (spriteSheet != NULL)
	{
		SDL_DestroyTexture(spriteSheet);
	}

}

void Animation::draw(int frame, int x, int y)
{
	// get current frame clipping region

	SDL_Rect clip;
	clip.x = frame * frameWidth; // frame 0-2 100*0, 100* 1, 100* 2

	clip.y = 0;

	clip.w = frameWidth;
	clip.h = frameHeight;

	// setup where frame should be drawn with destination rectangle

	SDL_Rect dest = { x - offsetX, y - offsetY, frameWidth, frameHeight }; // x, y, w, h

	SDL_RenderCopy(renderer, spriteSheet, &clip, &dest);
}
