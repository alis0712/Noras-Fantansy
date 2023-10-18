#include "Pangolin.h"

void Pangolin::setName(string newName)
{
	if(newName.length() > 0)
	{
		name = newName;
	
	}

	else
	{
		cout << "Please input name that is not empty!" << endl;
	}


}

string Pangolin::getName()
{
	return name;
}

void Pangolin::eatAnts(int ants)
{
	antsEaten = antsEaten + ants;
}

void Pangolin::displayStats()
{
	cout << "Pangolin: " << name << " antsEaten: " << antsEaten << endl;

}
