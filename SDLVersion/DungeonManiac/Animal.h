#pragma once
#include <iostream> // input and output stream
#include <string>

using namespace std;


class Animal
{

public:
	string name;
	int age;

	Animal();

	Animal(string name, int age);

	~Animal();

	virtual void eat(); // virtual allows for unique versions for each of the child classes
	virtual void makeSound();
	void display();

};

