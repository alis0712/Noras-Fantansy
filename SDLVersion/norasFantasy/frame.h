#pragma once

#ifndef FRAME
#define FRAME

// C++ includes
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>

// SDL and includes provided by professor
#include "SDL.h"
#include "drawing_functions.h"
#include "globals.h"
#include "groupBuilder.h"


using namespace std;


class Frame
{
public:	
	
	int frameNumber; // or frame index
	SDL_Rect clip; // its the region on the spritesheet where this frame is

	float duration; // how long does frame run for
	SDL_Point offSet; // pivot point to help align frames in an animation

	list<Group*> frameData; // holds groups of additional data for the frame

	void Draw(SDL_Texture* spriteSheet, float x, float y);

	// TODO loadframe

	void loadFrame(ifstream& file, list<DataGroupType>& groupTypes);




};

#endif
