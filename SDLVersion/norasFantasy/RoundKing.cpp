#include "RoundKing.h"

// animations
const string RoundKing::ROUND_KING_ANIM_IDLE = "idle";
const string RoundKing::ROUND_KING_ANIM_CHARGE = "charge";
const string RoundKing::ROUND_KING_ANIM_SHOOT = "shoot";
const string RoundKing::ROUND_KING_ANIM_SLAM = "slam";


const string RoundKing::ROUND_KING_ANIM_JUMP_TELEGRAPH = "jumpTelegraph";
const string RoundKing::ROUND_KING_ANIM_JUMP = "jump";
const string RoundKing::ROUND_KING_ANIM_DIE = "die";

// states
const int RoundKing::ROUND_KING_STATE_IDLE = 1;
const int RoundKing::ROUND_KING_STATE_CHARGE = 2;
const int RoundKing::ROUND_KING_STATE_SHOOT = 3;
const int RoundKing::ROUND_KING_STATE_SLAM = 4;
const int RoundKing::ROUND_KING_STATE_JUMP_TELEGRAPH = 5;
const int RoundKing::ROUND_KING_STATE_JUMP = 6;
const int RoundKing::ROUND_KING_STATE_DEAD = 7;

// phases
const int RoundKing::ROUND_KING_PHASE_NORMAL = 1;
const int RoundKing::ROUND_KING_PHASE_DAMAGED = 2;
const int RoundKing::ROUND_KING_PHASE_FRANTIC = 3;




RoundKing::RoundKing(AnimationSet* animSet, AnimationSet* bulletAnimSet)
{
	this->animSet = animSet;
	this->bulletAnimSet = bulletAnimSet;

	type = "enemy";

	x = Globals::ScreenWidth / 2;
	y = Globals::ScreenHeight / 2;

	moveSpeed = 0;
	moveSpeedMax = 20;
	hp = hpMax = 500;

	damage = 0;
	collisionBoxW = 50;
	collisionBoxH = 30;

	collisionBox.w = collisionBoxW;
	collisionBox.h = collisionBoxH;

	collisionBoxYOffset = -14;

	changeAnimation(ROUND_KING_STATE_IDLE, true);

	updateCollisionBox();

}

void RoundKing::update()
{
	// check if dead
	if (hp < 1 and state != ROUND_KING_STATE_DEAD)
	{
		changeAnimation(ROUND_KING_STATE_DEAD, true);
		moving = false;
		die();
	}

	// ai thinks what to do
	think();

	// update all shooting stuff
	/*if (state == ROUND_KING_STATE_SHOOT)
	{
		shootTimer -= TimeController::timeController.dT;
		shotTimer -= TimeController::timeController.dT;

		// if shooting time is over, stop shooting
		if (shootTimer <= 0)
		{
			changeAnimation(ROUND_KING_STATE_IDLE, true);
		}

		else if (shotTimer <= 0) // otherwise if still shooting and its time to take a shot
		{
			shotTimer = 0.5;

			Bullet* bullet = new Bullet(bulletAnimSet, x, y);

			SoundManager::soundManager.playSound("shoot");
			bullet->angle = angle;
			Entity::entities.push_back(bullet);

		}
	}*/

	updateShoot();
	
	updateCollisionBox();
	
	updateMovement();
	
	updateCollisions(); // checks if collisions are there and along the way 
	
	updateHitBox(); // update hitbox to show where damaging areas are
	
	updateDamages(); // update damage values, could be doing a certain amount of damage, dependent on the frames

	updateAnimation(); 
	
	updateInvincibleTimer(); // little bit of timer where they can't get hurt
	

}

void RoundKing::updateShoot()
{
	if (state == ROUND_KING_STATE_SHOOT)
	{
		shootTimer -= TimeController::timeController.dT;
		shotTimer -= TimeController::timeController.dT;

		// if shooting time is over, stop shooting
		if (shootTimer <= 0)
		{
			changeAnimation(ROUND_KING_STATE_IDLE, true);
		}

		else if (shotTimer <= 0) // otherwise if still shooting and its time to take a shot
		{
			shotTimer = 0.5;

			Bullet* bullet = new Bullet(bulletAnimSet, x, y);

			SoundManager::soundManager.playSound("shoot");
			bullet->angle = angle;
			Entity::entities.push_back(bullet);

		}
	}
}

void RoundKing::think()
{
	// finds the closest herp
	findNearestTarget();

	// if there is a hero we can target, do the thinking
	if (target != NULL)
	{
		// only tick down think timer if IDLE state
		if (state == ROUND_KING_STATE_IDLE)
		{
			thinkTimer -= TimeController::timeController.dT;
		}

		// keep setting angle to point towards a target
		angle = Entity::angleBetweenTwoEntities(this, target);
		 
		// check which phase we are in
		if (hp > 250)
		{
			aiState = ROUND_KING_PHASE_NORMAL;
		}

		else if (hp > 100)
		{
			aiState = ROUND_KING_PHASE_DAMAGED;
		}

		else // less than 100
		{
			aiState = ROUND_KING_PHASE_FRANTIC;
		}

		// if think timer is up work out what to do next
		if (thinkTimer <= 0 and state == ROUND_KING_STATE_IDLE)
		{
			// reset animations we are about to something new

			frameTimer = 0;
			// in normal phase do:
			if (aiState == ROUND_KING_PHASE_NORMAL)
			{
				// reset timer 
				thinkTimer = 2;

				// randomly select either slam or charge

				int action = getRandomNumber(4);


				if (action % 2 == 0)
				{
					slam();
				}

				else
				{
					// if odd number then
					charge();
				}
			}

			else if (aiState == ROUND_KING_PHASE_DAMAGED) // damage phase
			{
				// reset timer 
				thinkTimer = 1.5;

				// randomly select either slam or charge or jump

				int action = getRandomNumber(6);
				
				if (action < 2)
				{
					slam();
				}

				else if (action < 4)
				{
					charge();
				}

				else
				{
					jumpTelegraph();
				}
			}

			else // assuming we are frantic phase
			{
				// reset timer 
				thinkTimer = 1;

				int action = getRandomNumber(4);
				if (action % 2 == 0)
				{
					jumpTelegraph();
				}

				else
				{
					charge();
				}
			}
		}


	}

	else
	{
		// target no one - won't really unless hero some how disappears
		moving = 0;
		changeAnimation(ROUND_KING_STATE_IDLE, (state != ROUND_KING_STATE_IDLE));
	}

}

// Action functions
void RoundKing::charge()
{
	// preparing to shoot at you
	moving = false;
	SoundManager::soundManager.playSound("laugh");
	changeAnimation(ROUND_KING_STATE_CHARGE, true);

}

void RoundKing::shoot()
{
	moving = false;

	// 5 seconds of shooting at player
	shootTimer = 5;
	
	// take first shot immediately during shooting time
	shotTimer = 0;

	// if damaged, have a shorter shooting time
	if (aiState != ROUND_KING_PHASE_NORMAL)
	{
		shootTimer = 3;
	}

	changeAnimation(ROUND_KING_STATE_SHOOT, true);



}

void RoundKing::slam()
{
	moving = false;
	changeAnimation(ROUND_KING_STATE_SLAM, true);


}

void RoundKing::jumpTelegraph()
{
	moving = false;
	frameTimer = 0;
	changeAnimation(ROUND_KING_STATE_JUMP_TELEGRAPH, true);
}

void RoundKing::jump()
{
	moving = false;
	frameTimer = 0;
	slideAmount = 100;
	slideAngle = angle;
	changeAnimation(ROUND_KING_STATE_JUMP, true);


}

void RoundKing::die()
{

	moving = false;
	changeAnimation(ROUND_KING_STATE_DEAD, true);
	SoundManager::soundManager.playSound("enemyDie");

	// TODO add 1 roundKings Killed
	roundKingsKilled++;
}

void RoundKing::findNearestTarget()
{
	// TODO cleaner solution
	// suggest make another class to help with targeting entities, and make glob, grob, roundKing inherit from it
	
	target = NULL;

	// find closest target

	for (auto entity = Entity::entities.begin(); entity != Entity::entities.end(); entity++)
	{
		if ((*entity)->type == "hero" and (*entity)->active)
		{
			// if found first hero in list, just set them as the target for now
			if (target == NULL)
			{
				target = (LivingEntity*)(*entity); // if can't cast to LivingEntity, throw casting exception
			}

			else
			{
				// otherwise, is this other hero closer than the previous target
				if (Entity::distanceBetweenTwoEntities(this, (*entity)) < Entity::distanceBetweenTwoEntities(this, target))
				{
					target = (LivingEntity*)(*entity); // target is the new entity we just found that's closer
				}
			}
		}
	}

}

void RoundKing::changeAnimation(int newState, bool resetFrameToBeginning)
{
	state = newState;

	if (state == ROUND_KING_STATE_IDLE)
	{
		currentAnim = animSet->getAnimation(ROUND_KING_ANIM_IDLE);
	}

	if (state == ROUND_KING_STATE_CHARGE)
	{
		currentAnim = animSet->getAnimation(ROUND_KING_ANIM_CHARGE);
	}

	if (state == ROUND_KING_STATE_SHOOT)
	{
		currentAnim = animSet->getAnimation(ROUND_KING_ANIM_SHOOT);
	}

	if (state == ROUND_KING_STATE_SLAM)
	{
		currentAnim = animSet->getAnimation(ROUND_KING_ANIM_SLAM);
	}

	if (state == ROUND_KING_STATE_JUMP_TELEGRAPH)
	{
		currentAnim = animSet->getAnimation(ROUND_KING_ANIM_JUMP_TELEGRAPH);
	}

	if (state == ROUND_KING_STATE_JUMP)
	{
		currentAnim = animSet->getAnimation(ROUND_KING_ANIM_JUMP);
	}

	if (state == ROUND_KING_STATE_DEAD)
	{
		currentAnim = animSet->getAnimation(ROUND_KING_ANIM_DIE);
	}

	if (resetFrameToBeginning)
	{
		currentFrame = currentAnim->getFrame(0);
	}

	else
	{
		currentFrame = currentAnim->getFrame(currentFrame->frameNumber);
	}
}

void RoundKing::updateAnimation()
{
	if (currentFrame == NULL or currentAnim == NULL)
	{
		return;
	}

	frameTimer += TimeController::timeController.dT;

	// if frameTimer is greater than frame duration:
	if (frameTimer >= currentFrame->duration)
	{
		// if at the end of the last frame
		if (currentFrame->frameNumber == currentAnim->getEndFrameNumber())
		{
			if (state == ROUND_KING_STATE_CHARGE)
			{
				shoot();
			}

			else if (state == ROUND_KING_STATE_JUMP_TELEGRAPH)
			{
				jump();
			}

			else if (state == ROUND_KING_STATE_SLAM or state == ROUND_KING_STATE_JUMP)
			{
				changeAnimation(ROUND_KING_STATE_IDLE, true);
			}

			else if (state == ROUND_KING_STATE_DEAD)
			{
				frameTimer = 0;
				
				// if somehow alive again
				if (hp > 0)
				{
					changeAnimation(ROUND_KING_STATE_IDLE, true);
				}

				else
				{
					active = false; // get rid of them
				}
			}
		}

		else // not end of animation, so move to the next frame normally
		{
			currentFrame = currentAnim->getNextFrame(currentFrame);

			// if the new frame is dealing damage, we might want to make sounds
			GroupNumber* damages = (GroupNumber*)GroupBuilder::findGroupByName("damage", currentFrame->frameData);

			// if does damage
			if (damages != NULL and damages->numberOfDataInGroup() > 0)
			{
				// and if its slam state
				if (state == ROUND_KING_STATE_SLAM)
				{
					SoundManager::soundManager.playSound("smash");
				}

				else if (state == ROUND_KING_STATE_JUMP) // if in jump state
				{
					SoundManager::soundManager.playSound("crash");
				}
			}
		}

		frameTimer = 0;
	}
}

void RoundKing::updateDamages() // things hurt me
{
	// am i hittable
	if (active and hp > 0 and invincibleTimer <= 0)
	{
		for (auto entity = Entity::entities.begin(); entity != Entity::entities.end(); entity++)
		{
			if ((*entity)->active and (*entity)->type == "hero")
			{
				// cast to livingEntity pointer
				LivingEntity* enemy = (LivingEntity*)(*entity);

				// if enemy is hitting me
				if (enemy->damage > 0 and Entity::checkCollision(collisionBox, enemy->hitBox))
				{
					enemy->hitLanded(this);
					hp -= enemy->damage;

					if (hp > 0)
					{
						SoundManager::soundManager.playSound("enemyHit");
						invincibleTimer = 0.1;
					}
				}

			}
		}
	}

}

// die timer
int RoundKing::roundKingsKilled = 0; // increment this everytime we die



