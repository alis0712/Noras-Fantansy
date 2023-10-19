#include "entity.h"


const int Entity::DIR_UP = 0, Entity::DIR_DOWN = 1, Entity::DIR_RIGHT = 2, 
Entity::DIR_LEFT = 3, Entity::DIR_NONE = -1; // doesn't matter what their values as long as they are different

void Entity::update()
{
	// override me to do something useful
	
}

void Entity::draw()
{
	// override me if you want something else or more specific to happen

	// draws current frame
	if (currentFrame != NULL && active)
	{
		currentFrame->Draw(animSet->spriteSheet, x - Globals::camera.x, y - Globals::camera.y);
	}

	// draw collisionBox

	if (solid && Globals::debugging) // only one active color at a time
	{
		// sets the current drawing color and doesn't affect texture and what not
		SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

		SDL_RenderDrawRect(Globals::renderer, &collisionBox);


	}


}

void Entity::move(float angle)
{
	moving = true;
	moveSpeed = moveSpeedMax;
	this->angle = angle;

	int newDirection = angleToDirection(angle);

	// if direction changed, update current animation

	if (direction != newDirection)
	{
		direction = newDirection;
		changeAnimation(state, false);
	}
}

void Entity::updateMovement()
{
	updateCollisionBox();

	// store collisions before we move
	lastCollisionBox = collisionBox;
	
	// reset total moves
	totalXMove = 0;
	totalYMove = 0;

	if (moveSpeed > 0)
	{
		// works out move distance using speed, dt (time since last loop) and multiplies by lerp
		float moveDist = moveSpeed * (TimeController::timeController.dT) * moveLerp; // dT is usually very small

		if (moveDist > 0)
		{
			// xmove = distance * cos(angle in radians)
			float xMove = moveDist * (cos(angle * Globals::PI / 180));

			// ymove = distance * cos(angle in radians)
			float yMove = moveDist * (sin(angle * Globals::PI / 180));

			x += xMove;
			y += yMove;

			totalXMove = xMove;
			totalYMove = yMove;

			if (!moving)
			{
				moveSpeed -= moveDist;
			}


		}
	}

	// sliding around!
	if (slideAmount > 0)
	{
		float slideDist = slideAmount * TimeController::timeController.dT * moveLerp;

		if (slideDist > 0)
		{
			float xMove = slideDist * (cos(slideAngle * Globals::PI / 180));
				
				
			float yMove = slideDist * (sin(slideAngle * Globals::PI / 180));

			x += xMove;
			y += yMove;

			totalXMove += xMove;
			totalYMove += yMove;
			slideAmount -= slideDist;
		}

		else
		{
			slideAmount = 0;
		}
	}

	// now that we have moved, move the collisionBox up to where we are now
	updateCollisionBox();
	
	// to help with collision checking, unioin collisonBox with lastCollisionBox
	SDL_UnionRect(&collisionBox, &lastCollisionBox, &collisionBox);
}

void Entity::updateCollisionBox()
{
	collisionBox.x = x - collisionBox.w / 2;
	collisionBox.y = y + collisionBoxYOffset;

	collisionBox.w = collisionBoxW;
	collisionBox.h = collisionBoxH;


}

void Entity::updateCollisions()
{
	if (active && collideWithSolids && (moveSpeed > 0 || slideAmount > 0))
	{
		// list of potential collisions

		list<Entity*> collisions;

		// Broad phase - from where I started moving to where I end up moving
		for (list<Entity*>::iterator entity = Entity::entities.begin(); entity != Entity::entities.end(); entity++) // auto entity = Entity::entities.begin entity != Entity::entities.end(); entity++)is another way doing this
		{
			// if we collide with this entity with our currently unioned collisionbox, add to the list
			if ((*entity)->active 
				and (*entity)->type != this->type 
				and (*entity)->solid 
				and Entity::checkCollision(collisionBox, (*entity)->collisionBox)) // don't want enemies bumping into each other and don't walls bumping onto other walls
			{
				// add it to the list
				collisions.push_back(*entity);
			}
		}

		

		// if we have a list of potential entities we may hit, then lets check them properly to do collision resolution
		if (collisions.size() > 0)
		{
			updateCollisionBox();

			float collisionTime = 1; // 1 means no collisions, anything less, example 0.234 means we collided part of the way of our movement

			float normalX, normalY; // to help out which side we crash into stuff

			// our collisionBox before we tried to move 
			SDL_Rect startingCollisionBox = lastCollisionBox;

			// loop through the entities that are in our short list from loophole

			for (auto entity = collisions.begin(); entity != collisions.end(); entity++)
			{
				// temporary variables for normal x and y and also temp collisionTime
				float tmpNormalX, tmpNormalY;
				float tmpCollisionTime = SweptAABB(startingCollisionBox, totalXMove, totalYMove, (*entity)->collisionBox, tmpNormalX, tmpNormalY);

				// if this tmpCollisionTime is less then last collisionTime , use it instead

				if (tmpCollisionTime < collisionTime)
				{
					collisionTime = tmpCollisionTime;
					normalX = tmpNormalX;
					normalY = tmpNormalY;
				}

			}

			// if there was a collision, lets slide off of it
			if (collisionTime < 1.0f)
			{
				// if we die on solids, run the crash function
				if (dieOnSolids)
				{
					crashOntoSolid();
				}

				// Move our collisionBox position up to where we collided

				startingCollisionBox.x += totalXMove * collisionTime;
				startingCollisionBox.y += totalYMove * collisionTime;

				// how much move time was remaining
				float remainingTime = 1.0f - collisionTime;

				// update entities x and y to where we bumped into other entity

				x = startingCollisionBox.x + startingCollisionBox.w / 2;
				y = startingCollisionBox.y - collisionBoxYOffset;

				// collision response: slide, can't rub along the wall
				// work out dot product using remaining time
				float dotProd = (totalXMove * normalY + totalYMove * normalX) * remainingTime;

				totalXMove = dotProd * normalY;
				totalYMove = dotProd * normalX;
				x += totalXMove;
				y += totalYMove;

				//store collisionBox at this point
				lastCollisionBox = startingCollisionBox;

				// update our entities main collisionBox
				updateCollisionBox();

				// because our sliding may have bumped into other objects better run the function again 
				updateCollisions();

			}


		//	// multisample check for collisions from where we started to where we are planning to go t

		//	// first we are going to find the sample distance we should travel b/w checks
		//	float boxTravelSize = 0;
		//	if (collisionBox.w < collisionBox.h)
		//	{
		//		boxTravelSize = collisionBox.w / 4;
		//	}

		//	else
		//	{
		//		boxTravelSize = collisionBox.h / 4;
		//	}

		//	// use sample box check for collision from start point to end point, moving at boxTravelSize each sample
		//	SDL_Rect sampleBox = lastCollisionBox;

		//	float collisionMoveX = sampleBox.x, collisionMoveY = sampleBox.y;
		//	
		//	float movementAngle = Entity::angleBetweenTwoRects(lastCollisionBox, collisionBox);

		//	bool foundCollision = false;

		//	while (!foundCollision)
		//	{
		//		// check sampleBox for collisions where it is now
		//		SDL_Rect intersection;

		//		for (auto entity = collisions.begin(); entity != collisions.end(); entity++)
		//		{
		//			if (SDL_IntersectRect(&sampleBox, &(*entity)->collisionBox, &intersection)) // if there is an interesection it returns true and if there is no interesection it returns false
		//			{
		//				foundCollision = true;
		//				moveSpeed = 0;
		//				moving = false;
		//				slideAngle = angleBetweenTwoEntities((*entity), this);

		//				// currently intersecting a entitym now we need to do collision resolution
		//				if (intersection.w < intersection.h)
		//				{
		//					if (lastCollisionBox.x + lastCollisionBox.w / 2 < (*entity)->collisionBox.x + (*entity)->collisionBox.w / 2)
		//					{
		//						sampleBox.x -= intersection.w; // staered on left, so move out of collision
		//					}
		//					else
		//					{
		//						sampleBox.x += intersection.w; // otherwise, started on right
		//					}
		//				}

		//				else
		//				{
		//					if (lastCollisionBox.y + lastCollisionBox.h / 2 < (*entity)->collisionBox.y + (*entity)->collisionBox.h / 2)
		//					{
		//						sampleBox.y -= intersection.h; // started above so move up out of collision 
		//					}
		//					else
		//					{
		//						sampleBox.y += intersection.h; // otherwise, started below
		//					}
		//				}
		//			}
		//		}

		//		// if collisionsfound or sampleBox is at sample place as collisonBox, exit loop

		//		if (foundCollision or (sampleBox.x == collisionBox.x && sampleBox.y == collisionBox.y))
		//		{
		//			break;
		//		}

		//		// move sample box up to check the spot
		//		if (distanceBetweenTwoRects(sampleBox, collisionBox) > boxTravelSize)
		//		{
		//			movementAngle = Entity::angleBetweenTwoRects(sampleBox, collisionBox);
		//			float xMove = boxTravelSize * (cos(movementAngle * Globals::PI / 180)); // 0.71

		//			float yMove = boxTravelSize * (sin(movementAngle * Globals::PI / 180));

		//			/*sampleBox.x += xMove;
		//			sampleBox.y += yMove;*/

		//			// fix for float values below 1 example 0.71 being truncated to sampleBox.x as thats an int
		//			collisionMoveX += xMove;
		//			collisionMoveY += yMove;

		//			sampleBox.x = collisionMoveX;
		//			sampleBox.y = collisionMoveY; 
		//		}
		//		else
		//		{
		//			sampleBox = collisionBox;
		//		}
		//	}

		//	if (foundCollision)
		//	{
		//		// move our entity to where the sampleBox ended up
		//		slideAmount = slideAmount / 2;
		//		x = sampleBox.x + sampleBox.w / 2;
		//		y = sampleBox.y - collisionBoxYOffset;
		//	}

		//	updateCollisionBox(); 

		}

		
	}

	


}


// Helper functions

// --- AABB Function Implementation Begin ---

// return type: gives 0-1 depending on where collision is, 1 means no collisions and 0 means collide immediately and 0.5 means half etc

// params: movingBox is entity being checked
		// vx and vy are the velocities our moving box is moving at
		// other box is some other entities collision box we may collide with
		// normal x and normal y let us know which side of the otherBox we colided with, these are pass by reference


float Entity::SweptAABB(SDL_Rect movingBox, float vx, float vy, SDL_Rect otherBox, float& normalX, float& normalY)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y

	if (vx > 0.0f)
	{
		xInvEntry = otherBox.x - (movingBox.x + movingBox.w); // LHS of moving Box
		xInvExit = (otherBox.x + otherBox.w) - movingBox.x; // RHS of moving box
	}

	else
	{
		xInvEntry = (otherBox.x + otherBox.w) - movingBox.x; // swaps - RHS
		xInvExit = (otherBox.x) - (movingBox.x + movingBox.w); // swaps - LHS
	}

	if (vy > 0.0f)
	{
		yInvEntry = otherBox.y - (movingBox.y + movingBox.h);
		yInvExit = (otherBox.y + otherBox.h) - movingBox.y;
	}

	else
	{
		yInvEntry = (otherBox.y + otherBox.h) - movingBox.y; // swaps - RHS
		yInvExit = (otherBox.y) - (movingBox.y + movingBox.h); // swaps - LHS
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent dividing by zero)

	float xEntry, yEntry;
	float xExit, yExit;

	if (vx == 0.0f)
	{
		// use the limits thing
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();

	}

	else
	{
		xEntry = xInvEntry / vx; // diving by 0
		xExit = xInvExit / vx;
	}

	if (vy == 0.0f)
	{
		// use the limits thing
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();

	}

	else
	{
		//yEntry = xInvEntry / vx; // diving by 0
		//yExit = xInvExit / vx;

		yEntry = yInvEntry / vy; // diving by 0
		yExit = yInvExit / vy;
	}

	// find the earliest and latest times of collision
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// if there was No collision
	if (entryTime > exitTime or xEntry < 0.0f and yEntry < 0.0f or xEntry > 1.0f or yEntry > 1.0f)
	{
		normalX = 0.0f; // no x normal
		normalY = 0.0f; // no y mormal

		return 1.0f; // 1 mean moved full distance, no collisions
	}

	else
	{
		// there was a collision and we have hit something

		// we should work out which sides/normals of the otherBox we collided with
		if (xEntry > yEntry)
		{
			// assuming we have hit the otherbox on the x-axis
			if (xInvEntry < 0.0f)
			{
				normalX = 1; // hit RHS
				normalY = 0; // not hit top or bottom of otherBox
			}

			else
			{
				normalX = -1; // hit LHS
				normalY = 0; // not hit top or bottom of otherBox
			}
		}

		else
		{
			// assumes we hit othrBox on y-axis
			if (yInvEntry < 0.0f)
			{
				normalX = 0;
				normalY = 1;
			}

			else
			{
				normalX = 0;
				normalY = -1;
			}
		}
		
		// return time of collision (0-1 ex 0.234234)
		return entryTime;
		
	}
	// return 0.0f;
}

// --- AABB Function Implementation End ---


float Entity::distanceBetweenTwoRects(SDL_Rect& r1, SDL_Rect& r2)
{
	SDL_Point e1, e2;
	e1.x = r1.x + r1.w / 2;
	e1.y = r1.y + r1.h / 2;

	e2.x = r2.x + r2.w / 2;
	e2.y = r2.y + r2.h / 2;

	float d = abs(sqrt(pow(e2.x - e1.x, 2) + pow(e2.y - e1.y, 2)));

	return d;
}

float Entity::distanceBetweenTwoEntities(Entity* e1, Entity* e2)
{
	float d = abs(sqrt(pow(e2->x - e1->x, 2) + pow(e2->y - e1->y, 2)));
	return d;
}


float Entity::distanceBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2)
{
	float d = abs(sqrt(pow(cx2 - cx1, 2) + pow(cy2 - cy1, 2))); // knock of all the negative values

	return d;
}

float Entity::angleBetweenTwoEntities(Entity* e1, Entity* e2)
{
	float dx, dy;

	float x1 = e1->x, y1 = e1->y, x2 = e2->x, y2 = e2->y;

	/*if (e1->solid)
	{

	}*/

	dx = x2 - x1;
	dy = y2 - y1;
	
	return atan2(dy, dx) * 180 / Globals::PI;
}

bool Entity::checkCollision(SDL_Rect cbox1, SDL_Rect cbox2)
{
	SDL_Rect intersection;
	if (SDL_IntersectRect(&cbox1, &cbox2, &intersection))
	{
		return true;
	}

	//if a rectangle is in another rectangle
		//do it here

	return false;
}

int Entity::angleToDirection(float angle)
{
	if ((angle >= 0 and angle <= 45) or angle >= 315 and angle <= 360)
	{
		return DIR_RIGHT;
	}

	else if (angle >= 45 and angle <= 90 + 45)
	{
		return DIR_DOWN;
	}

	else if (angle >= 90 + 45 and angle <= 180 + 45)
	{
		return DIR_LEFT;
	}

	else
	{
		return DIR_UP;
	}

}
	


float Entity::angleBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2)
{
	float dx = cx2 - cx1;
	float dy = cy2 - cy1;

	return atan2(dy, dx) * 180 / Globals::PI;
}

float Entity::angleBetweenTwoRects(SDL_Rect& r1, SDL_Rect& r2)
{
	float cx1 = r1.x + (r1.w / 2);
	float cy1 = r1.y + (r1.h / 2);

	float cx2 = r2.x + (r2.w / 2);
	float cy2 = r2.y + (r2.h / 2);

	return angleBetweenTwoPoints(cx1, cy1, cx2, cy2);
}

// global entities list I can refer to at anytime

list<Entity*> Entity::entities; // redundant not sure if this is needed

bool Entity::EntityCompare(const Entity* const& a, const Entity* const& b)
{

	if (a != 0 and b != 0)
	{
		return (a->y < b->y);
	}

	else
	{
		return false;

	}

}

void Entity::removeInactiveEntitiesFromList(list<Entity*>* entityList, bool deleteEntities)
{
	for (auto entity = entityList->begin(); entity != entityList->end();) // entity++) // list of entities iterator or pointing a position in the list
	{
		// if entity is not active
		if (!(*entity)->active)
		{
			if (deleteEntities)
			{
				delete(*entity);
			}
			entity = entityList->erase(entity);
		}

		else
		{
			entity++;
		}
	}
}

void Entity::removeAllFromList(list<Entity*>* entityList, bool deleteEntities)
{
	for (auto entity = entityList->begin(); entity != entityList->end();) // entity++) // list of entities iterator or pointing a position in the list
	{

		if (deleteEntities)
		{
			delete(*entity);
		}
		entity = entityList->erase(entity);
		
		
		// if entity is not active
		/*if ((*entity)->active)
		{
			if (deleteEntities)
			{
				delete(*entity);
			}
			entity = entityList->erase(entity);
		}*/

		/*else
		{
			entity++;
		}*/
	}

}

Entity::Entity()
{


}
