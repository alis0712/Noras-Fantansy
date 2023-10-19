#include "soundManager.h"

SoundManager::SoundManager()
{
	// not needed

}

SoundManager::~SoundManager()
{
	// todo
	for (list<soundListing>::iterator sl = sounds.begin(); sl != sounds.end(); sl++)
	{
		Mix_FreeChunk(sl->sound); // cleans up all the dynamic memory when we load up our sounds
	}
}

void SoundManager::loadSound(string name, string file)
{
	soundListing listing;
	listing.name = name;
	listing.sound = Mix_LoadWAV(file.c_str());

	sounds.push_back(listing); // reference them whenever you would like to play them


}

void SoundManager::playSound(string name)
{
	for (list<soundListing>::iterator sl = sounds.begin(); sl != sounds.end(); sl++)
	{
		if (sl->name == name)
		{
			Mix_PlayChannel(-1, sl->sound, 0);
			break;
		}
	}

}

SoundManager SoundManager::soundManager;
