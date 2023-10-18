#include "Mimic.h"


Mimic::Mimic()
{
	hp = 25;
	hpMax = 25;
	str = 6;
	def = 1;
	agi = 2;
}



Mimic::~Mimic()
{

}


string Mimic::getName()
{
    return "Mimic";
}
