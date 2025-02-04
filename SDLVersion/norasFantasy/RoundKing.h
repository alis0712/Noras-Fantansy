#pragma once
#ifndef ROUND_KING
#define ROUND_LING

#include <cstdlib>
#include "livingEntity.h"
#include "soundManager.h"
#include "Bullet.h"

using namespace std;


class RoundKing: public LivingEntity
{
public:
	// animations
	static const string ROUND_KING_ANIM_IDLE;
	static const string ROUND_KING_ANIM_CHARGE;
	static const string ROUND_KING_ANIM_SHOOT;
	static const string ROUND_KING_ANIM_SLAM;


	static const string ROUND_KING_ANIM_JUMP_TELEGRAPH;
	static const string ROUND_KING_ANIM_JUMP;
	static const string ROUND_KING_ANIM_DIE;

	// states
	static const int ROUND_KING_STATE_IDLE;
	static const int ROUND_KING_STATE_CHARGE;
	static const int ROUND_KING_STATE_SHOOT;
	static const int ROUND_KING_STATE_SLAM;
	static const int ROUND_KING_STATE_JUMP_TELEGRAPH;
	static const int ROUND_KING_STATE_JUMP;
	static const int ROUND_KING_STATE_DEAD;

	// phases
	static const int ROUND_KING_PHASE_NORMAL;
	static const int ROUND_KING_PHASE_DAMAGED;
	static const int ROUND_KING_PHASE_FRANTIC;


	// when zero do new action
	float thinkTimer = 0;

	// how long to shoot for
	float shootTimer = 0;

	// how long between bullets
	float shotTimer = 0;

	// who should i chase
	LivingEntity* target = NULL;

	// current phase for boss
	int aiState = ROUND_KING_PHASE_NORMAL;

	// reference to bullet animations
	AnimationSet* bulletAnimSet;

	static int roundKingsKilled;

	// constructor
	RoundKing(AnimationSet* animSet, AnimationSet* bulletAnimSet);
	
	// update functions
	void update();
	void updateShoot();
	
	void think();
	void charge();
	void shoot();
	void slam();
	void jumpTelegraph();
	void jump();
	void die();
	void findNearestTarget(); // TODO: move find nearest target to somewhere better, maybe static

	void changeAnimation(int newState, bool resetFrameToBeginning);
	void updateAnimation();
	void updateDamages();

};
#endif

