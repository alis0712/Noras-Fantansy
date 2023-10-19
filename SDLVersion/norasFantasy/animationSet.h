#pragma once
#ifndef ANIMATIONSET
#define ANIMATIONSET

#include "Animation.h"

using namespace std;


class AnimationSet
{
public:

	string imageName;
	SDL_Texture* spriteSheet; // holds the sprite sheet image for all of our animations

	SDL_Texture* whiteSpriteSheet = NULL; // I use this sprite sheet to show damage

	list<Animation> animations;

	~AnimationSet(); // properly cleans up any dynamic memory example textures
	
	Animation* getAnimation(string name);

	// TODO loadAnimationSet

	void loadAnimationSet(string fileName, list<DataGroupType>& groupTypes, bool setColorKey = false, int transparentPixelIndex = 0, bool createWhiteTexture = false);


};

#endif