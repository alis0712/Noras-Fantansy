#pragma once
#ifndef ENTITY
#define ENTITY

// AABB Collision Implementation
#include <limits>
#include <algorithm>


#include "globals.h"
#include "timeController.h"
#include "animationSet.h"

// Abstract Class, cannot instantiate an object of type Entity e.g cannot do Entity e;
class Entity
{
public:
	// reference constants
	static const int DIR_UP, DIR_DOWN, DIR_RIGHT, DIR_LEFT, DIR_NONE;

	// it'll be different for each entity - so a hero would have states like attacking, walking, you get the idea
	// quick label to see what the entity is up to
	int state;
	
	float x, y;
	int direction;
	bool solid = true; // is thing solid, can things can pass through me
	bool collideWithSolids = true;// sometimes we are solid but I pass through other solids

	// new adds for AABB
	bool dieOnSolids = false; // useful if you need entities to die on touching solids for example bullet hit wall




	bool active = true; // entity turned on or off

	string type = "entity"; // what type of entity is it example herom enemy, wall, etc

	bool moving; // is the entity moving yes or no

	float angle; // angle to move entity in (360 degree angle) 

	float moveSpeed; // how fast we are going

	float moveSpeedMax; // top speed

	float slideAngle; // direction pushed in

	float slideAmount; // amount of push in the slide angle

	float moveLerp = 4;

	float totalXMove, totalYMove; // keeps track of total x, y movement turn, just in case we need to retract movement

	SDL_Rect collisionBox; // box describing the size of our entity and this is use to bump into things

	SDL_Rect lastCollisionBox; // where our collision box was last 

	int collisionBoxW, collisionBoxH; // our default collisionbox sizes

	float collisionBoxYOffset; // from my entities y value, where should I draw this collisionBox

	AnimationSet* animSet; // set of all animations this entity can have
	Animation* currentAnim; // current animation the entity is using

	Frame* currentFrame; // the current frame in the above animation the entity using

	float frameTimer; // helps animate frame to frame

	// Functions to built - must be Virtual

	virtual void update();

	virtual void draw();

	virtual void move(float angle);

	virtual void updateMovement();

	virtual void updateCollisionBox();

	virtual void changeAnimation(int newState, bool resetFrameToBeginning) = 0; // fully abstract function now

	virtual void updateCollisions(); // how we bump stuff in the world

	virtual void crashOntoSolid()
	{
		; // if dieOnSoilds is true, then this function will deal with the dying
	}

	// helper functions

	// -- added for AABB --
	static float SweptAABB(SDL_Rect movingBox, float vx, float vy, SDL_Rect otherBox, float& normalX, float& normalY);

	static float distanceBetweenTwoRects(SDL_Rect& r1, SDL_Rect& r2);

	static float distanceBetweenTwoEntities(Entity* e1, Entity* e2);

	// -- added for AABB--
	static float distanceBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2);

	static float angleBetweenTwoEntities(Entity* e1, Entity* e2);

	static bool checkCollision(SDL_Rect cbox1, SDL_Rect cbox2);

	// static int angleToDirection(float Float);
	static int angleToDirection(float angle);

	static float angleBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2);

	static float angleBetweenTwoRects(SDL_Rect& r1, SDL_Rect& r2);

	static list <Entity*> entities; // list of entities that acts like a global entities list taht i can refer to at any time

	static bool EntityCompare(const Entity* const& a, const Entity* const& b); // helps compare two entities in a list to help with sorting (sorts based on y value), decides the drawing order for all the entities

	static void removeInactiveEntitiesFromList(list<Entity*>* entityList, bool deleteEntities); 

	static void removeAllFromList(list<Entity*>* entityList, bool deleteEntities);

	// constructor
	Entity();

};

#endif

