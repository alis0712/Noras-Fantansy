#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Hero.h"
#include "MapObject.h"
#include <list> // arrays are good fixed number of object, lists is a container that can shrink and grow, alternatives could have been vector, map, queue or a stack


#include <fstream> // file stream
#include "InfoBox.h"

#include <stdlib.h> // useful functions including rand and srand
#include <time.h> // time in seconds since start of year

#include "BattleScreen.h"

using namespace std;



class MapScreen
{
public:
	Hero* hero; // it'll reference hero built inside main.cpp
	int* items; // going to use this to reference items[10] from main.cpp

	SDL_Renderer* renderer;
	// 2D array representing the map, 0 values = walls, 1 = values = can walk/ground
	
	int map[10][10];
	
	MapObject heroObj;
	MapObject door;
	
	list<MapObject> mapObjects; // a container that can contain a bunch of things like strings, vectors, and so forth

	SDL_Texture* heroTexture, * doorTexture, * globTexture, * chestTexture;

	bool quit = false;
	bool escaped = false;
	bool doorLocked = true;

	InfoBox infoBox;

	MapScreen(SDL_Renderer* renderer, Hero* hero, int* items);
	~MapScreen();

	void itemFound();

	void update();
	void draw();

};

