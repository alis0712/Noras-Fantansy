#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	currentAnimation = NULL;
	currentFrame = 0; 
	frameTimer = 0;
	animationEnded = false;
	loopAnimation = true;
}

void AnimationManager::changeAnimation(Animation* animation)
{
	currentAnimation = animation;
	/*currentFrame = 0;
	frameTimer = 0;
	animationEnded = false;*/
	resetAnimation(); // refactored code
}

void AnimationManager::setAnimationLooping(bool loopAnimation)
{
	this->loopAnimation = loopAnimation;
}

void AnimationManager::resetAnimation()
{
	currentFrame = 0;
	frameTimer = 0;
	animationEnded = false;
}

void AnimationManager::update(float dt)
{
	if (currentAnimation != NULL)
	{
		// update frametimer
		frameTimer = frameTimer + dt; // or frameTimer += dt

		// if this frame has been shown long enough
		if (frameTimer >= currentAnimation->frameDuration)
		{
			// move onto the next frame
			currentFrame++;

			// reset frame timer
			frameTimer = 0;

			// check to see if the current frame is past the last frame of our animation
			if (currentFrame >= currentAnimation->numberOfFrames)
			{
				// gone past the end
				if (loopAnimation)
				{
					currentFrame = 0;
				}

				else
				{
					// we finished this animation
					animationEnded = true;
					// make the currentFrame the last one in the set
					currentFrame = currentAnimation->numberOfFrames - 1;
				}
			}
		}
	}
}

void AnimationManager::draw(int x, int y)
{
	if (currentAnimation != NULL)
	{
		(*currentAnimation).draw(currentFrame, x, y);
	}
}
