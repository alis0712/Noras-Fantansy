#pragma once

#ifndef LIVINGENTITY
#define LIVINGENTITY

#include "entity.h"

// abstract class also

class LivingEntity: public Entity
{
public:
	int hp, hpMax;
	int damage = 0;
	SDL_Rect hitBox; // similar to collisionBox, but describes damaging area

	float invincibleTimer = 0; // if > 0, then can't be hurt

	virtual void updateHitBox();
	virtual void updateDamages() = 0; // how we get damaged by other things (up to each class to define)
	virtual void die() = 0; // abstract, up to other classes to decide how they die

	virtual void updateInvincibleTimer();

	virtual void hitLanded(LivingEntity* entity) { ; }

	void draw(); // overriding entities draw


	LivingEntity();

	
};

#endif

