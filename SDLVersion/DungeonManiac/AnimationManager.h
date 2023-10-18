#pragma once

#include "Animation.h"


class AnimationManager
{
public:
	Animation* currentAnimation;
	int currentFrame; // frame index starting from 0
	float frameTimer; // keeps track of how long the current frame has been on the screen
	
	bool animationEnded; // flag to let us know when animation is done
	
	bool loopAnimation; // true for keep repeating animation, false for stop when done

	AnimationManager();

	void changeAnimation(Animation* animation);
	void setAnimationLooping(bool loopAnimation);
	void resetAnimation();
	
	
	void update(float dt); // need delta time to work out frame timer
	void draw(int x, int y);



};

