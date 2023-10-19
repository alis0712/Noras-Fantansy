#include "game.h"

Game::Game()
{
	string resPath = getResourcePath();
	
	backgroundImage = loadTexture(resPath + "map.png", Globals::renderer);

	splashImage = loadTexture(resPath + "cyborgtitle.png", Globals::renderer);

	overlayImage = loadTexture(resPath + "overlay.png", Globals::renderer);

	splashShowing = true;
	overlayTimer = 2;

	// setup camera
	Globals::camera.x = 0;
	Globals::camera.y = 0;
	Globals::camera.w = Globals::ScreenWidth;
	Globals::camera.h = Globals::ScreenHeight;

	// load up sounds
	SoundManager::soundManager.loadSound("hit", resPath +"Randomize2.wav");
	SoundManager::soundManager.loadSound("enemyHit", resPath +"Hit_Hurt9.wav");
	SoundManager::soundManager.loadSound("swing", resPath + "Randomize21.wav");
	SoundManager::soundManager.loadSound("dash", resPath + "dash.wav");
	SoundManager::soundManager.loadSound("growl", resPath + "Randomize34.wav");
	SoundManager::soundManager.loadSound("enemyDie", resPath + "Randomize41.wav");

	// load sounds for the boss battle
	SoundManager::soundManager.loadSound("crash", resPath + "crash.wav");
	SoundManager::soundManager.loadSound("smash", resPath + "smash.wav");
	SoundManager::soundManager.loadSound("shoot", resPath + "shoot2.wav");
	SoundManager::soundManager.loadSound("laugh", resPath + "laugh2.wav");




	//music
	song = Mix_LoadMUS(string(resPath + "Uka Uka.mp3").c_str()); // song by ryan beveridge

	if (song != NULL)
	{
		Mix_PlayMusic(song, -1); // -1 is infinite times
	}


	// create a list of data group types
	// holds a list of group types this list of group, this list describes the types of groups of data our frames can have

	list<DataGroupType> dataGroupTypes;

	// so what data group can have
	
	// collisonBoxes (although we have hardcoded the collison boxes
	DataGroupType colBoxType;
	colBoxType.groupName = "collisionBox";
	colBoxType.dataType = DataGroupType::DATATYPE_BOX;


	// hitBoxes
	DataGroupType hitBoxType;
	hitBoxType.groupName = "hitBox";
	hitBoxType.dataType = DataGroupType::DATATYPE_BOX;

	// damage
	DataGroupType dmgType;
	dmgType.groupName = "damage";
	dmgType.dataType = DataGroupType::DATATYPE_NUMBER;

	// add all of these datatypes to the list
	dataGroupTypes.push_back(colBoxType);
	dataGroupTypes.push_back(hitBoxType);
	dataGroupTypes.push_back(dmgType);


	// we are making all of this as it will help us load information

	heroAnimSet = new AnimationSet();
	heroAnimSet->loadAnimationSet("udemyCyborg.fdset", dataGroupTypes, true, 0, true);

	globAnimSet = new AnimationSet();
	globAnimSet->loadAnimationSet("glob.fdset", dataGroupTypes, true, 0, true);

	// TODO add grob enemy wave
	grobAnimSet = new AnimationSet();
	grobAnimSet->loadAnimationSet("grob.fdset", dataGroupTypes, true, 0, true);


	roundKingAnimSet = new AnimationSet();
	roundKingAnimSet->loadAnimationSet("roundKing.fdset", dataGroupTypes, true, 0, true);

	bulletAnimSet = new AnimationSet();
	bulletAnimSet->loadAnimationSet("bullet.fdset", dataGroupTypes, true, 0, true);

	wallAnimSet = new AnimationSet();
	wallAnimSet->loadAnimationSet("wall.fdset", dataGroupTypes);

	

	// build hero entity
	hero = new Hero(heroAnimSet);
	hero->invincibleTimer = 0;
	hero->x = Globals::ScreenWidth / 2;
	hero->y = Globals::ScreenHeight / 2;

	// tells keyboard input to manage hero
	heroInput.hero = hero;

	// add hero to the entity list
	Entity::entities.push_back(hero);

	// add a camera controller - get camera to follow hero
	camController.target = hero;
	


	int tileSize = 32;

	// build all the walls for this game
	
	// first build walls on top and botton of the screen

	for (int i = 0; i < Globals::ScreenWidth / tileSize; i++)
	{
		// fills in top row
		Wall* newWall = new Wall(wallAnimSet);
		newWall->x = i * tileSize + tileSize/2; // because the origin of the wall in the fdset is in its center
		newWall->y = tileSize / 2;
		walls.push_back(newWall);
		Entity::entities.push_back(newWall);

		// reusing pointer to create a bottom row
		newWall = new Wall(wallAnimSet);
		newWall->x = i * tileSize + tileSize / 2; // because the origin of the wall in the fdset is in its center
		newWall->y = Globals::ScreenHeight - tileSize / 2;
		walls.push_back(newWall);
		Entity::entities.push_back(newWall);

	}

	// now the sides
	for (int i = 1; i < Globals::ScreenHeight / tileSize - 1; i++)
	{
		// fills in left column
		Wall* newWall = new Wall(wallAnimSet);
		newWall->x = tileSize / 2; // because the origin of the wall in the fdset is in its center
		newWall->y = i * tileSize + tileSize / 2;
		walls.push_back(newWall);
		Entity::entities.push_back(newWall);

		// reusing pointer to create a right column
		newWall = new Wall(wallAnimSet);
		newWall->x = /*i * tileSize*/ Globals::ScreenWidth - tileSize / 2; // because the origin of the wall in the fdset is in its center
		// newWall->y = Globals::ScreenHeight - tileSize / 2;
		newWall->y = i * tileSize + tileSize / 2;
		walls.push_back(newWall);
		Entity::entities.push_back(newWall);
	}

	buildBossNext = false;
	bossActive = false;

	// TODO add hpbar


	// setup herohpBar's x and y to be centered
	herohpBar.x = Globals::ScreenWidth / 2.0f - (herohpBar.barWidth / 2.0); // centered horizontally
	herohpBar.y = Globals::ScreenHeight - herohpBar.barHeight - 310; // touching the bottom of the screen and -20 pixels to buffer it off the bottom

	// setup hpBar's x and y to be centered
	hpBar.x = Globals::ScreenWidth / 2.0f - (hpBar.barWidth / 2.0); // centered horizontally
	hpBar.y = Globals::ScreenHeight - hpBar.barHeight - 20; // touching the bottom of the screen and -20 pixels to buffer it off the bottom

}

Game::~Game()
{

	cleanup(backgroundImage);
	cleanup(splashImage);
	cleanup(overlayImage);

	Mix_PausedMusic();
	Mix_FreeMusic(song); // cleans it up

	if (scoreTexture != NULL) // if used then cleanup
	{
		cleanup(scoreTexture);
	}



	Entity::removeAllFromList(&Entity::entities, false); // dynamic memory

	delete heroAnimSet;
	delete globAnimSet;
	delete grobAnimSet;
	delete wallAnimSet;
	delete roundKingAnimSet;
	delete bulletAnimSet;

	delete hero;

	// delete all of the wall entities
	Entity::removeAllFromList(&walls, true);
	Entity::removeAllFromList(&enemies, true);
}

void Game::update()
{
	// enemy related
	int enemiesToBuild = 2;
	int enemiesBuilt = 0;
	float enemyBuildTimer = 1;

	bool quit = false;

	

	SDL_Event e;

	// setup my time controller before the game starts

	TimeController::timeController.reset();

	// game loop
	while (!quit)
	{
		TimeController::timeController.updateTime(); // freeze time if we ever need to

		Entity::removeInactiveEntitiesFromList(&Entity::entities, false);

		// remove/delete the enemies in the enemies list who are dead/inactive
		Entity::removeInactiveEntitiesFromList(&enemies, true);



		// check for any events that might have happened
		while (SDL_PollEvent(&e)) // three things happened at once finds the first event and processes and keeps the same process for second and third keys
		{
			// close the window - check for those events as well
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			// if keydowm event
			if (e.type == SDL_KEYDOWN)
			{
				// switch case on which button was pressed
				switch (e.key.keysym.scancode)
				{
				
				case SDL_SCANCODE_ESCAPE: // esc key 
					quit = true;
					break;
				
				case SDL_SCANCODE_SPACE:
					if (splashShowing)
					{
						splashShowing = false;
					}

					if (overlayTimer <= 0 and hero->hp < 1)
					{
						// then cleanup and restart the game
						enemiesToBuild = 2;
						enemiesBuilt = 0;
						enemyBuildTimer = 3;
						overlayTimer = 2;
						enemyWavesTillBoss = 3;
						bossActive = false;
						buildBossNext = false;

						// make hpBar point to no entities health
						herohpBar.entity = NULL;
						hpBar.entity = NULL;
						

						RoundKing::roundKingsKilled = 0;
						Glob::globsKilled = 0;
						Grob::grobsKilled = 0;
						// RoundKing::roundKingsKilled = 0;

						if (scoreTexture != NULL)
						{
							cleanup(scoreTexture);
							scoreTexture = NULL;
						}

						// remove all existing enemies
						for (list<Entity*>::iterator enemy = enemies.begin(); enemy != enemies.end(); enemy++)
						{
							(*enemy)->active = false; // get cleaned up later
						}
						hero->revive();
					}
					hero->revive(); // handy for testing
					break;

				}
			}
			heroInput.update(&e);
		}

		// make a overlay timer tick down
		if (hero->hp < 1 and overlayTimer > 0)
		{
			overlayTimer -= TimeController::timeController.dT;
		}

		// update all entities
		for (list<Entity*>::iterator entity = Entity::entities.begin(); entity != Entity::entities.end(); entity++)
		{
			// remember how awesome polymorphism is?
			// update all entities in game world is at once
			(*entity)->update();

		}

		// spawn enemies
		if (hero->hp > 0 and !splashShowing)
		{
			
			herohpBar.entity = hero;
			if (enemiesToBuild == enemiesBuilt and enemies.size() <= 0)
			{
				// enemiesToBuild = enemiesToBuild * 2; // good enough to create an interesting battle
				enemiesToBuild = enemiesToBuild + 2; // good enough to create an interesting battle

				enemiesBuilt = 0;

				enemyBuildTimer = 4;
				enemyWavesTillBoss--;

				if (enemyWavesTillBoss <= 0)
				{
					buildBossNext = true;
				}


			}

			enemyBuildTimer -= TimeController::timeController.dT;

			// if no bosses on the prowl, check to see if we build some jerks
			
			if (!buildBossNext and !bossActive and enemyBuildTimer <= 0 and enemiesBuilt < enemiesToBuild and enemies.size() < 10) // want o build less than 10 enemies at any given stage
			{
				Glob* enemy = new Glob(globAnimSet);

				// set enemies position somewhere random within the arean's open space
				enemy->x = getRandomNumber(Globals::ScreenWidth - (2 * 32) - 32 /*tileSize*/) + 32 + 16; // give me a random so that we are not spawning on the lHS ever + 16 factors in their offset
				enemy->y = getRandomNumber(Globals::ScreenHeight - (2 * 32) - 32 /*tileSize*/) + 32 + 16;
				enemy->invincibleTimer = 0.1;

				enemies.push_back(enemy);
				Entity::entities.push_back(enemy);

				enemiesBuilt++;
				enemyBuildTimer = 1;

				if (enemiesBuilt % 5 == 0)
				{
					Grob* grob = new Grob(grobAnimSet);
					grob->x = getRandomNumber(Globals::ScreenWidth - (2 * 32) - 32) + 32 + 16; //random x value between our walls
					grob->y = getRandomNumber(Globals::ScreenHeight - (2 * 32) - 32) + 32 + 16; //random x value between our walls
					grob->invincibleTimer = 0.01;

					enemies.push_back(grob);
					Entity::entities.push_back(grob);
				}


			}

			

			// for the boss
			if (buildBossNext and enemyBuildTimer <= 0 and enemies.size() == 0 )
			{
				RoundKing* round = new RoundKing(roundKingAnimSet, bulletAnimSet);
				round->invincibleTimer = 0.1;
				enemies.push_back(round);
				Entity::entities.push_back(round);

				// make hpBar point to boss
				hpBar.entity = round;

				bossActive = false;
				buildBossNext = false;
				enemyWavesTillBoss = 3;
			}

			// if there was a boss but he is dead now, go back to spawning normal enemies till the next boss
			if (bossActive and enemies.size() == 0)
			{
				bossActive = false;
				buildBossNext = false;
				enemiesBuilt = 0;
				enemiesToBuild = 2;

				// when boss dead, make sure hpBar doesn't reference him anymore
				hpBar.entity = NULL;
			}
		}

		
		// update camera positions
		camController.update();


		// draw all entities
		draw();

	}

}

void Game::draw()
{
	// clear the screen
	SDL_SetRenderDrawColor(Globals::renderer, 145, 133, 129, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Globals::renderer);

	if (splashShowing)
	{
		renderTexture(splashImage, Globals::renderer, 0, 0);

	}

	else
	{
		// draw the background first
		// renderTexture(backgroundImage, Globals::renderer, 0, 0);
		renderTexture(backgroundImage, Globals::renderer, 0 - Globals::camera.x, 0 - Globals::camera.y);



		// sort all entities based on y-depth
		Entity::entities.sort(Entity::EntityCompare);


		// draw all of the entities
		for (list<Entity*>::iterator entity = Entity::entities.begin(); entity != Entity::entities.end(); entity++)
		{
			// remember how awesome polymorphism is?
			// update all entities in game world is at once
			(*entity)->draw();
		}

		SDL_Color Hero = { 0, 255, 0, SDL_ALPHA_OPAQUE };
		SDL_Color Boss = { 240, 51, 159, SDL_ALPHA_OPAQUE };

		// Draw UI stuff
		herohpBar.draw(Hero); // Draw herohpBar in green
		hpBar.draw(Boss);   // Draw hpBar in the default color


		if (overlayTimer <= 0 and hero->hp < 1)
		{
			renderTexture(overlayImage, Globals::renderer, 0, 0);

			if (scoreTexture == NULL)
			{
				// generate the score text
				SDL_Color color = { 255, 255, 255, 255 }; // white

				stringstream ss;
				ss << "Enemies dispatched: " << Glob::globsKilled + Grob::grobsKilled + RoundKing::roundKingsKilled;

				string resPath = getResourcePath();
				scoreTexture = renderText(ss.str(), resPath + "vermin_vibes_1989.ttf", color, 30, Globals::renderer);
			}
			renderTexture(scoreTexture, Globals::renderer, 20, 50);
		}
	}

	//// draw the background first
	//renderTexture(backgroundImage, Globals::renderer, 0, 0);

	//// sort all entities based on y-depth
	//Entity::entities.sort(Entity::EntityCompare);


	//// draw all of the entities
	//for (list<Entity*>::iterator entity = Entity::entities.begin(); entity != Entity::entities.end(); entity++)
	//{
	//	// remember how awesome polymorphism is?
	//	// update all entities in game world is at once
	//	(*entity)->draw();
	//}
	
	// after we are done drawing/rendering show it to the screen
	SDL_RenderPresent(Globals::renderer);


}


