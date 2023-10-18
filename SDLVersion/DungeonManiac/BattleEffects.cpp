#include "BattleEffects.h"



void BattleEffects::setup(SDL_Renderer* renderer, int x, int y)
{

	this->renderer = renderer;
	this->x = x;
	this->y = y;

	// load all effect animations
	hit.setup("assets/hit.png", renderer, 4, 0.1f, 54, 107);
	heal.setup("assets/heal.png", renderer, 4, 0.1f, 54, 107);
	explode.setup("assets/hit.png", renderer, 4, 0.1f, 54, 107);
	attackBoost.setup("assets/atkBoost.png", renderer, 4, 0.1f, 31, 134);
	defenceBoost.setup("assets/defBoost.png", renderer, 4, 0.1f, 31, 134);



}

void BattleEffects::setXY(int x, int y)
{
	this->x = x;
	this->y = y;

}

void BattleEffects::doHit()
{
	animationManager.changeAnimation(&hit);
	animationManager.setAnimationLooping(false);
	doAction = true;

}

void BattleEffects::doHeal()
{
	animationManager.changeAnimation(&heal);
	animationManager.setAnimationLooping(false);
	doAction = true;
}

void BattleEffects::doExplode()
{
	animationManager.changeAnimation(&explode);
	animationManager.setAnimationLooping(false);
	doAction = true;

}

void BattleEffects::doAttackBoost()
{
	animationManager.changeAnimation(&attackBoost);
	animationManager.setAnimationLooping(false);
	doAction = true;

}

void BattleEffects::doDefenceBoost()
{
	animationManager.changeAnimation(&defenceBoost);
	animationManager.setAnimationLooping(false);
	doAction = true;
}

void BattleEffects::update(float dt)
{
	if (doAction)
	{
		animationManager.update(dt);
		if (animationManager.animationEnded)
		{
			doAction = false;
		}
	}
}

void BattleEffects::draw()
{
	if (doAction)
	{
		animationManager.draw(x, y);
	}
}
