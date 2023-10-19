#pragma once

#ifndef HPBAR
#define HPBAR

#include "livingEntity.h"


class HPBar
{
public:
	int x, y;
	int barWidth = 200, barHeight = 30; // how big it is going to be


	LivingEntity* entity = NULL;

	// virtual void draw();
	virtual void draw(const SDL_Color& color);


};

#endif

