#pragma once


// C++ standard libraries
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include<SDL_ttf.h>

// Character libaries
#include "Hero.h"
#include "Glob.h"
#include "Mimic.h"
#include "CharacterType.h"
#include "CharacterAnimationSet.h"
#include "HPBar.h"
#include "BattleButton.h"
#include "BattleEffects.h"
#include "ItemMenu.h"


// TODO More

using namespace std;


class BattleScreen
{
public:
	SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture;

	Hero* hero;
	int* items; // pointer for our items array

	Character* enemy;

	bool battleFinished;
	bool quit;
	bool heroesTurn = true;

	SDL_Texture* nameTexture;
	SDL_Rect nameRect;
	CharacterAnimationSet heroAnimationSet;
	CharacterAnimationSet enemyAnimationSet;
	
	// hp for the enemy and hero
	HPBar heroHP;
	HPBar enemyHP;
	
	// battle buttons during combat
	BattleButton fightButton;
	BattleButton itemButton;

	// hero Damage
	int heroDmg = 0, enemyDmg = 0;

	// Batte effects
	BattleEffects battleEffects;


	// TODO add lots more

	BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items, CharacterType enemyType);
	ItemMenu itemMenu;
	
	
	~BattleScreen();

	bool animationsPlaying();
	void useItem();

	void update();
	
	void draw();


};

