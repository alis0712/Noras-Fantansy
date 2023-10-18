#pragma once

#include <iostream>
#include <string>
#include "Character.h"

using namespace std;



// inherits from the character class
class Hero : public Character
{
private:
	string name;

public:

	void setName(string s);

	// replace getName inherited from character
	string getName();

	void heal(int amount);
	void atkBoost(int amount);
	void defBoost(int amount);

};

