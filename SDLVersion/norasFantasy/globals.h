#pragma once

#ifndef GLOBALS
#define GLOBALS // multiple definitions of this class if pragma or define is not added


#include <string>
#include <iostream>
#include <SDL.h>

#include "randomNumber.h"

using namespace std;

class Globals
{
public:

	// math helpers
	static const float PI; // static - it doesn't belong to individual object of type Global, this data member is shared among all the Globals

	// useful for us as a dev
	static bool debugging;

	// sdl related stuff
	static int ScreenWidth, ScreenHeight, ScreenScale;

	static SDL_Renderer* renderer;

	// clips off header e.g. "clip: 50 114 44 49" turns into "50 114 44 49" just spits out the numbers
	static string clipOffDataHeader(string data);

	// camera
	static SDL_Rect camera;






};

#endif


