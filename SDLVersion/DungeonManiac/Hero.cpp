#include "Hero.h"

void Hero::setName(string s)
{
	name = s;

}

string Hero::getName()
{
	return name;
}

void Hero::heal(int amount)
{
	hp += amount; // hp = hp + amount
	
	if (hp > hpMax)
	{
		hp = hpMax;
	}

}

void Hero::atkBoost(int amount)
{
	str += amount;

}

void Hero::defBoost(int amount)
{
	def += amount;

}
