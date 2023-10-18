#pragma once
#include "AnimationManager.h"
#include "CharacterType.h"

using namespace std;


class CharacterAnimationSet
{
public:


	int x, y;
	SDL_Renderer* renderer;
	Animation idle, attack, hit;
	AnimationManager animationManager;

	// for animation that play once and then return to idle
	bool doAction;

	// CharacterAnimationSet();

	void setup(SDL_Renderer* renderer, int x, int y, CharacterType type);

	void doIdle();

	void doAttack();

	void doHit();

	void update(float dt);

	void draw();

};

