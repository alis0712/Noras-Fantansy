#include "MapScreen.h"

MapScreen::MapScreen(SDL_Renderer* renderer, Hero* hero, int* items)
{
	// Note: computer code random is psuedorandom (fake random)
	// setting a seed value for the random algorithm will generate a set of numbers which appear random
	// if we use the same seed value then we'll get the exact same 'random' outcomes
	// therefore we will set the seed as a changing value, the seconds since start of the year
	// so the seed value is different each time we run through the game

	srand(time(NULL));

	this->renderer = renderer;
	this->hero = hero;
	this->items = items;

	// loop through the map using nested loop and clear all values to be zero (walls)

	//for (int x = 0; x <= 9; x++)
	//{
	//	// map[i][i] will make me go diagonally
	//	for (int y = 0; y <= 9; y++)
	//	{
	//		map[x][y] = 0;
	//	}
	//}
	
	// manual room building -- old for testing
	
	map[1][1] = 1;
	map[2][1] = 1;
	map[3][1] = 1;
	
	
	map[1][2] = 1;
	map[2][2] = 1;
	map[3][2] = 1;

	// mo is map objects

	// Open Map text file
	fstream mapFile("assets/map.txt");
	if (mapFile.is_open())
	{
		for (int y = 0; y <= 9; y++)
		{
			// map[i][i] will make me go diagonally
			for (int x = 0; x <= 9; x++)
			{
				// map[x][y] = 0;
				char grid = '\n'; // hold a single keyboard symbol

				// read in a single character from where we are up to in the file
				mapFile >> grid; // input one character at a time
				// mapFile << "Jellyfish";
				if (grid == '0')
				{
					map[x][y] = 0; // wall
				}
				else
				{
					map[x][y] = 1; // land

					// TODO was it a hero, glob, chest or mimic???
					if (grid == 'h')
					{
						heroObj.type = 1;
						heroObj.x = x;
						heroObj.y = y;
					}

					else if (grid == 'd')
					{
						door.type = 2;
						door.x = x;
						door.y = y;
					}
					else if (grid == 'c')
					{
						MapObject chest;
						chest.type = 5;
						chest.x = x;
						chest.y = y;

						mapObjects.push_back(chest);
					}

					else if (grid == 'g')
					{
						MapObject glob;
						glob.type = 3;
						glob.x = x;
						glob.y = y;

						mapObjects.push_back(glob);
					}

					else if (grid == 'm')
					{
						MapObject mimic;
						mimic.type = 4;
						mimic.x = x;
						mimic.y = y;

						mapObjects.push_back(mimic);
					}
					
				}
			}
		}
	}

	// close file
	mapFile.close();

	// load up tile textures
	heroTexture = IMG_LoadTexture(renderer, "assets/girlTile.png");
	doorTexture = IMG_LoadTexture(renderer, "assets/doorTile.png");
	globTexture = IMG_LoadTexture(renderer, "assets/globTile.png");
	chestTexture = IMG_LoadTexture(renderer, "assets/chestTile.png");

	// setup info box
	infoBox.setup(renderer);
	infoBox.setText("Welcome to the Dungeon Maniac!!!!");



}

MapScreen::~MapScreen()
{
	// clean up texture memory
	SDL_DestroyTexture(heroTexture);
	SDL_DestroyTexture(doorTexture);
	SDL_DestroyTexture(globTexture);
	SDL_DestroyTexture(chestTexture);


}

void MapScreen::itemFound()
{
	// randomly pick an item between 1 and 4, if it were between 10 and 14 then move it up by a value of 10
	int item = rand() % 4 + 1; // rand gets next number out of random number set (value between 0-2147483647)
	// try and find a free slot for this item
	bool freeSlotFound = false;

	for (int i = 0; i < 10; i++)
	{
		// once find free slot, set it to the item and exit out of the loop
		if (items[i] == 0)
		{
			freeSlotFound = true;
			items[i] = item;
			break; // exits the loop
		}
	}

	if (freeSlotFound == true)
	{
		if (item == 1)
		{
			infoBox.setText("Found Vanilla!");
		}

		else if (item == 2)
		{
			infoBox.setText("Found Grenade!");
		}

		else if (item == 3)
		{
			infoBox.setText("Found Attack Boost!");
		}

		else if (item == 4)
		{
			infoBox.setText("Found Defence Boost!");
		}

		else
		{
			infoBox.setText("Bag's Full Mate!");
		}

		infoBox.visible = true;
	}

}

void MapScreen::update()
{
	// read user inputs including keyboard, mouse, gamepads, screen resize/close, touchscreens, etc

	SDL_Event sdlEvent;

	// loop through input events and copy their details one by one into our sdlEvent variable
	while (SDL_PollEvent(&sdlEvent))
	{
		// event when user clicks close window button
		if (sdlEvent.type == SDL_QUIT)
		{
			quit = true;
		}

		// if the button was pressed 
		if (sdlEvent.type == SDL_KEYDOWN)
		{
			// then check which button
			// did they press esc key?

			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				quit = true;
			}
			// hide info when space is pressed
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				infoBox.visible = false;
			}

			if(infoBox.visible == false && hero->getHP() > 0)
			{
				// TODO Player Movement
				int hx = heroObj.x;
				int hy = heroObj.y;

				// right for dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					// hero move right
					hx++;
				}

				// left for dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					// hero move left
					hx--;
				}

				// right for dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					// hero move down
					hy++;
				}

				// left for dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					// hero move left
					hy--;
				}

				// if hx and hy are within the grid
				if (hx >= 0 && hx <= 9 && hy >= 0 && hy <= 9 && map[hx][hy] == 1) // land for us
				{
					// set heroObj.x and y to hx and hy
					heroObj.x = hx;
					heroObj.y = hy;

					// can we escape the dungeon?
					if (!doorLocked and !escaped and heroObj.x == door.x and heroObj.y == door.y)
					{
						infoBox.setText("Congrats!!! You escaped!!!!!!!");
						infoBox.visible = true;
						escaped = true;
					}

					// see if we walked onto a map object
					// for(int i = 1; i <= 10; i++) // same as this for loop when using lists
					for (list<MapObject>::iterator mo = mapObjects.begin(); mo != mapObjects.end(); mo++)
					{
						// Iterator is a special pointer pointing to a position in a list
						// dereferncing (*) iterator gives you access to the item at that point in the list
						
						// only interact with active map objects
						if ((*mo).active) // or mo->active
						{
							// is hero's x, y overlapping this map object's x, y
							if (heroObj.x == mo->x && heroObj.y == mo->y)
							{
								mo->active = false;

								// check map objects type and deal with accordingly

								if (mo->type == 3)
								{
									// TODO battle glob
									BattleScreen battle(renderer, hero, items, globType);
									battle.update();

									if (battle.quit)
									{
										quit = true;
										// TODO deal with death
									}

									else if (hero->getHP() <= 0)
									{
										infoBox.setText("You Died!!!");
										infoBox.visible = true;
									}
								}

								else if(mo->type == 4)
								{
									// TODO battle mimic
									BattleScreen battle(renderer, hero, items, mimicType);
									battle.update();

									if (battle.quit)
									{
										quit = true;
										// TODO deal with death
									}

									else if (hero->getHP() <= 0)
									{
										infoBox.setText("You Died!!!");
										infoBox.visible = true;
									}

								}

								else if (mo->type == 5)
								{
									// open chest get item :)
									itemFound();
								}
									
							}
						}
					}
				}
				else
				{
					// invalid move don't need to do anything here
				}
			}
			

		}

	}

	// check to see if map objects all inactive and if we should unlock the door
	if (!infoBox.visible && doorLocked) // or (infoBox.visible != true) or (infoBox.visible == false)
	{
		bool monstersAlive = false;
		for (MapObject mo : mapObjects)
		{
			// if is a monster glob or mimic
			if (mo.type == 3 or mo.type == 4)
			{
				// if is active monster?
				if (mo.active)
				{
					monstersAlive = true;
					break;
				}
			}
		}

		// if all monsters are dead then unlock the door
		if (!monstersAlive)
		{
			doorLocked = false;
			infoBox.setText("The door is now unlocked!!!");
			infoBox.visible = true;
		}
	}

	// has user closed infobox after escaping

	if (!infoBox.visible and (escaped or hero->getHP() <= 0))
	{
		quit = true;
	}
}

void MapScreen::draw()
{
	// Map drawing 
	// tile representing size of 1 grid thing from map
	SDL_Rect tileRect = { 0, 0, 32, 32 };
	
	// loop through and draw each grid value from map array

	for (int x = 0; x <= 9; x++)
	{
		// map[i][i] will make me go diagonally
		for (int y = 0; y <= 9; y++)
		{
			// if is ground set draw color to ground 
			// else set to wall color
			if (map[x][y] == 1)
			{
				// ground
				SDL_SetRenderDrawColor(renderer, 136, 60, 100, 255);
			}

			else
			{
				// walls
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			}
			// Move rectangle to grid position with regards to tile width/height

			tileRect.x = x * tileRect.w;
			tileRect.y = y * tileRect.h;

			// draw rectangle to screen using current draw color
			SDL_RenderFillRect(renderer, &tileRect);
		}
	}

	// Draw map objects

	// draw hero
	tileRect.x = heroObj.x * tileRect.w; // example hero x = 4, y = 6, tile w = 32, h = 32
	tileRect.y = heroObj.y * tileRect.h;

	SDL_RenderCopy(renderer, heroTexture, NULL, &tileRect);

	// draw door
	tileRect.x = door.x * tileRect.w; // example hero x = 4, y = 6, tile w = 32, h = 32
	tileRect.y = door.y * tileRect.h;

	SDL_RenderCopy(renderer, doorTexture, NULL, &tileRect);

	// Draw map objects in the list

	// loop through list and draw each object

	for (MapObject mo : mapObjects) // a container of map objects being called out and is a copy
	{
		// Note: mo is a mapOjects copy from mapObjects and is not a direct reference to the mapObjects
		if (mo.active)
		{
			tileRect.x = mo.x * tileRect.w; // example hero x = 4, y = 6, tile w = 32, h = 32
			tileRect.y = mo.y * tileRect.h;

			if (mo.type == 3) // glob
			{
				SDL_RenderCopy(renderer, globTexture, NULL, &tileRect);
			}
			else // mimic or chest
			{
				SDL_RenderCopy(renderer, chestTexture, NULL, &tileRect);
			}
		}
	}

	// draw info box on top
	infoBox.draw(); 
}
