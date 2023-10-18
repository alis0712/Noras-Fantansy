#pragma once
// standard libraries
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_Image.h>

using namespace std;


class Animation
{
public:
	
	//basic info
	int numberOfFrames;
	int frameWidth, frameHeight;
	int offsetX, offsetY; // frame pivot point
	float frameDuration; // how long single frame shows on screen 1 = 1 second, 0.5 = 500 ms

	SDL_Texture* spriteSheet; // reference to existing texture

	SDL_Renderer* renderer;



	// Animation();

	void setup(string spriteSheetFile, SDL_Renderer* renderer, int numberOfFrames, float frameDuration, int offsetX, int offsetY); // want animations in other classes, so that it can be called anytime I want. and therefore a constructor won't have access SDL_Renderer anytime I want 
	
	~Animation();

	void draw(int frame, int x, int y);

};

