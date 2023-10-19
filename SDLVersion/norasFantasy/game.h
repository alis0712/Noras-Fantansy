#pragma once
#ifndef GAME
#define GAME

// Globals
#include "globals.h"

// Characters
#include "hero.h"
#include "wall.h"
#include "glob.h"
#include "grob.h"

// user inputs
#include "keyboardInput.h"
#include "drawing_functions.h"

// sound manager
#include "soundManager.h"

// camera controller
#include "CameraController.h"

// add a boss
#include "RoundKing.h"

// add hpBar
#include "hpBar.h"
#include "herohpBar.h"



class Game
{

public:
	Mix_Music* song;

	AnimationSet* heroAnimSet;

	AnimationSet* globAnimSet;

	AnimationSet* grobAnimSet;

	AnimationSet* wallAnimSet;

	// for added boss
	AnimationSet* roundKingAnimSet;

	AnimationSet* bulletAnimSet;



	SDL_Texture* backgroundImage;
	SDL_Texture* splashImage;
	SDL_Texture* overlayImage;

	SDL_Texture* scoreTexture = NULL; // for drawing strings to the screen



	Hero* hero;
	KeyboardInput heroInput;

	list<Entity*> enemies;
	list<Entity*> walls; // just to deal with wall

	int enemyWavesTillBoss = 3;
	bool buildBossNext = false;
	bool bossActive = false;
	
	heroHPBar herohpBar;
	HPBar hpBar;

	bool splashShowing;
	float overlayTimer;

	CameraController camController;

	Game();
	~Game(); // since we will deal a lot with dynamic memory

	void update();
	void draw();


};

#endif
