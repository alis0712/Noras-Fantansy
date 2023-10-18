#include "CharacterAnimationSet.h"

void CharacterAnimationSet::setup(SDL_Renderer* renderer, int x, int y, CharacterType type)
{
	this->renderer = renderer;
	this->x = x;
	this->y = y;

	if (type == heroType)
	{
		// load up hero animations
		idle.setup("assets/girlIdle.png", renderer, 1, 1, 40, 132);

		attack.setup("assets/girlPunch.png", renderer, 3, 0.1f, 69, 155);

		hit.setup("assets/girlHit.png", renderer, 2, 0.1f, 47, 145);
	}

	else if (type == globType)
	{
		// load up hero animations
		idle.setup("assets/globIdle.png", renderer, 1, 1, 36, 105);

		attack.setup("assets/globBite.png", renderer, 3, 0.1f, 93, 123);

		hit.setup("assets/globHit.png", renderer, 2, 0.1f, 62, 115);
	}

	else if (type == mimicType)
	{
		// load up hero animations
		idle.setup("assets/mimicIdle.png", renderer, 1, 1, 53, 65);

		attack.setup("assets/mimicAttack.png", renderer, 4, 0.1f, 151, 113);

		hit.setup("assets/mimicHit.png", renderer, 2, 0.1f, 45, 69);
	}

	doIdle();
}

void CharacterAnimationSet::doIdle()
{
	animationManager.changeAnimation(&idle);
	animationManager.setAnimationLooping(true);
	doAction = false;
}

void CharacterAnimationSet::doAttack()
{
	animationManager.changeAnimation(&attack);
	animationManager.setAnimationLooping(false);
	doAction = true;
}

void CharacterAnimationSet::doHit()
{
	animationManager.changeAnimation(&hit);
	animationManager.setAnimationLooping(false);
	doAction = true;
}

void CharacterAnimationSet::update(float dt)
{
	animationManager.update(dt);

	// if running action animation and that animation is finished

	if (animationManager.animationEnded && doAction)
	{
		doIdle(); // go back to idle animation state
	}
}

void CharacterAnimationSet::draw()
{
	animationManager.draw(x, y);
}
