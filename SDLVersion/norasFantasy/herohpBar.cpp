#include "herohpBar.h"


void heroHPBar::draw(const SDL_Color& color)
{
    if (entity != nullptr)
    {
        HPBar::draw(color); // Pass the color as a parameter

    }
}
