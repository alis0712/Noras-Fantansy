#include "Animal.h"

Animal::Animal()
{
	name = "Bob";
	age = 22;

}

Animal::Animal(string name, int age)
{
	this->name = name;
	this->age = age;



}

Animal::~Animal()
{

}

void Animal::eat()
{
	cout << name << " eats some food " << endl;

}

void Animal::makeSound()
{
	cout << name << " makes a strange sound " << endl;
}

void Animal::display()
{
	cout << "Animal: " << name << " age: " << age << endl;

}


