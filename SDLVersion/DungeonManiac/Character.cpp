#include "Character.h"

void Character::setupStats(int _hp, int _str, int _def, int _agi)
{
	hp = _hp;
	hpMax = _hp;
	str = _str;
	def = _def;
	agi = _agi;
}

void Character::displayStats()
{
	cout << "hp: " << hp << " / " << hpMax << " str: " << str << " def: " << def << " agi: " << agi << endl;

}

int Character::getHP()
{
	return hp;
}

int Character::getHPMax()
{
	return hpMax;
}

int Character::getAGI()
{
	return agi;
}

int Character::getDamage()
{
	return str;
}

void Character::takeDamage(int dmg)
{
	int dmgAfterDef = dmg - def;

	if (dmgAfterDef < 1)
	{
		dmgAfterDef = 1;
	}

	hp = hp - dmgAfterDef;

}

string Character::getName()
{
	return "Character";
}


