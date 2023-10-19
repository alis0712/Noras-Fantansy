#include "livingEntity.h"

void LivingEntity::updateHitBox()
{
	// assume damage 0 for now
	damage = 0;


	//// int x = (int)4.5; turn 4.5 into an if its possible 
	//casting with classes and polymorphism only works when if you are casting from something that it inherits from say group box inherits from group and
	//we are returing a group so we are giving a go and will crash if it returns a different type of group returns string for example

	GroupBox* hitBoxes = (GroupBox*)GroupBuilder::findGroupByName("hitBox", currentFrame->frameData); // one none or many on any of the data frame
	
	if (hitBoxes != NULL and hitBoxes->numberOfDataInGroup() > 0)
		// update hitbox
	{
		SDL_Rect hb = hitBoxes->data.front(); // gives the first data in the list which in this case is the SDL_Rect
		
		
		hitBox.x = x - currentFrame->offSet.x + hb.x;
		hitBox.y = y - currentFrame->offSet.y + hb.y;

		hitBox.w = hb.w;
		hitBox.h = hb.h;

		// update damage
		GroupNumber* damages = (GroupNumber*)GroupBuilder::findGroupByName("damage", currentFrame->frameData);

		if (damages != NULL and damages->numberOfDataInGroup() > 0)
		{
			damage = damages->data.front();
		}
	}

}

void LivingEntity::updateInvincibleTimer()
{
	if (invincibleTimer > 0)
	{
		invincibleTimer -= TimeController::timeController.dT;
	}

}

void LivingEntity::draw()
{
	// override me if you want something else or more specific to happen

	// draws current frame
	if (currentFrame != NULL && active)
	{
		if (invincibleTimer > 0 and animSet->whiteSpriteSheet != NULL)
		{
			//
			currentFrame->Draw(animSet->whiteSpriteSheet, x - Globals::camera.x, y - Globals::camera.y);
		}

		else
		{
			currentFrame->Draw(animSet->spriteSheet, x - Globals::camera.x, y - Globals::camera.y);
		}
		// currentFrame->Draw(animSet->spriteSheet, x, y);
	}

	// draw collisionBox

	if (solid && Globals::debugging) // only one active color at a time
	{
		// sets the current drawing color and doesn't affect texture and what not
		SDL_SetRenderDrawColor(Globals::renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &lastCollisionBox);

		SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &collisionBox);

		SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &hitBox);


	}

}

LivingEntity::LivingEntity()
{


}

//LivingEntity::LivingEntity()
//{
//
//
//}
