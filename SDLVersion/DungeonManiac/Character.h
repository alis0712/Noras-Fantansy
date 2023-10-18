#pragma once
#include <iostream>
#include <string>

using namespace std;


class Character
{
// private:
protected: // works the same as private, but children class can't access it

	// attributes
	int hp, hpMax, str, def, agi;

public:
	
	void setupStats(int _hp, int _str, int _def, int _agi);
	void displayStats();

	int getHP();
	
	int getHPMax();
	
	int getAGI();

	int getDamage();

	void takeDamage(int dmg);

	string getName();

};

