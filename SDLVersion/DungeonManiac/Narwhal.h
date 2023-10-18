#pragma once
#include "Animal.h"
class Narwhal :
    public Animal
{
public:
    float tuskSize; // in meters

    Narwhal();
    Narwhal(string name, int age, float tuskSize);
    
    
    ~Narwhal();

    void eat();
    void makeSound();
    void swim();


};

