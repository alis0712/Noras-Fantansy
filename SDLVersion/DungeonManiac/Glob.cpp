#include "Glob.h"

Glob::Glob()
{
    hp = 25;
    hpMax = 25;
    str = 6;
    def = 1;
    agi = 2; 

}

Glob::~Glob()
{


}

string Glob::getName()
{
    return "Glob";
}

void Glob::makeDumbNoise()
{
    cout << getName() << "makes a shrieking sound at you!" << endl;
}
