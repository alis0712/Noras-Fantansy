#pragma once

#ifndef TIMECONTROLLER
#define TIMECONTROLLER

#include <iostream>
#include "SDL.h"

class TimeController
{
public:
	// reference values 
	static const int PLAY_STATE, PAUSE_STATE;

	int timeState;
	Uint32 lastUpdate;// 21234455 // last time we checked how many ticks we were up to

	float dT; // delta time, int seconds ( 1 = 1 second, 0.5 half a second), time since the last frame was rendered into the screen

	TimeController();
	
	void updateTime(); // update lastUpdate and dT
	void pause();
	void resume();

	void reset();

	static TimeController timeController;
};


#endif
