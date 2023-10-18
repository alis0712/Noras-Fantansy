#pragma once


#include <iostream> // input and output stream
#include <string>

using namespace std;

// OOP - Object Oriented Programming
// Encapsulation - done
	// class contains attributes and behaviors

// Inheritance
// Polymorphism

class Pangolin
{
private:
	string name;


public:

	// attributes

	// string name;
	int antsEaten;

	// behaviors (functions belowing the class)

	void setName(string newName);
	string getName();

	void eatAnts(int ants);

	void displayStats();





};

