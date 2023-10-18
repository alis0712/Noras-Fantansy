#include "Narwhal.h"

Narwhal::Narwhal()
{
	name = "Narnar";
	age = 13;
	tuskSize = 1.7;


}

Narwhal::Narwhal(string name, int age, float tuskSize)
{
	this->name = name;
	this->age = age;
	this->tuskSize = tuskSize;
}

Narwhal::~Narwhal()
{


}

void Narwhal::eat()
{
	cout << name << "eats some squid" << endl;

}

void Narwhal::makeSound()
{
	cout << name << " makes some echolocation click sounds" << endl;

}

void Narwhal::swim()
{
	cout << name << " swims gracefully through cold water " << endl;

}

