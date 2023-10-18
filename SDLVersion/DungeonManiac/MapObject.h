#pragma once
class MapObject
{

public:
	// 1 = hero
	// 2 = door
	// 3 = glob
	// 4 = mimic
	// 5 = chest(note: mimic look like chest)


	int type;
	// position on map grid (map indexes)
	int x, y; // example map[x][y] is where an object may be

	// when not active, destroy this object
	bool active = true;



	// MapObject();

};

