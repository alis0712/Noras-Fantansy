#include "ItemMenu.h"

SDL_Texture* ItemMenu::generateTextTexture(TTF_Font* font, SDL_Color color, string text)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    return textTexture;

}

ItemMenu::~ItemMenu()
{
    SDL_DestroyTexture(noItem);
    SDL_DestroyTexture(vanilla);
    SDL_DestroyTexture(grenade);
    SDL_DestroyTexture(attackBoost);
    SDL_DestroyTexture(defenceBoost);
    SDL_DestroyTexture(cancel);

}

void ItemMenu::setup(SDL_Renderer* renderer, int* items, int x, int y)
{
    this->renderer = renderer;
    this->items = items;
    this->x = x;
    this->y = y;

    //Create Name Texture
    TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
    SDL_Color textColor = { 0,0,0,0 };

    // generate all text textures
    noItem = generateTextTexture(font, textColor, "--");
    vanilla = generateTextTexture(font, textColor, "Vanilla");
    grenade = generateTextTexture(font, textColor, "Grenade");
    attackBoost = generateTextTexture(font, textColor, "Attack Boost");
    defenceBoost = generateTextTexture(font, textColor, "Defence Boost");
    cancel = generateTextTexture(font, textColor, "Cancel");

    TTF_CloseFont(font);



}

void ItemMenu::moveUp()
{
    selectedItemIndex--;

    // smallest index is 0 in items array, so lets not go negative
    if (selectedItemIndex < 0)
    {
        selectedItemIndex = 0;
    }
}

void ItemMenu::moveDown()
{
    selectedItemIndex++;
    
    // highest index is 10 in items array (from 0 - 9 for items), but we are also including cancel therefore it goes from 0 - 10
    if (selectedItemIndex > 10)
    {
        selectedItemIndex =10;
    }

}

void ItemMenu::draw()
{
    if (!visible)
    {
        return; // skips rest of this function
    }

    SDL_Rect itemButton = { x, y, 100, 20 };

    // loop through 10 items + cancel for drawing to screen

    for (int i = 0; i < 10; i++)
    {
        // put button beneath previous button
        itemButton.y = y + (i * itemButton.h);

        // set items buttons background color based on if its selected or not
        if (selectedItemIndex == i)
        {
            SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
        }

        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        }

        // render button back color
        SDL_RenderFillRect(renderer, &itemButton);

        // setup texture pointer and work out which text texture we need for this item we are rendering
        SDL_Texture* tmpTexture = noItem;
        
        if (items[i] == 1)
        {
            tmpTexture = vanilla;
        }

        else if (items[i] == 2)
        {
            tmpTexture = grenade;
        }

        else if (items[i] == 3)
        {
            tmpTexture = attackBoost;
        }
        
        else if (items[i] == 4)
        {
            tmpTexture = defenceBoost;
        }

        SDL_Rect textRect;
        textRect.x = itemButton.x + 2;
        textRect.y = itemButton.y + 2;

        // get width of this texture we are pointing at
        SDL_QueryTexture(tmpTexture, NULL, NULL, &textRect.w, &textRect.h);

        // draw
        SDL_RenderCopy(renderer, tmpTexture, NULL, &textRect);
    }

    // and also do cancel button 
    if (selectedItemIndex == 10)
    {
        SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
    }

    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    }

    // put button beneath previous button
    itemButton.y = y + (10 * itemButton.h);
    SDL_RenderFillRect(renderer, &itemButton);

    SDL_Rect textRect;
    textRect.x = itemButton.x + 2;
    textRect.y = itemButton.y + 2;

    // get width of this texture we are pointing at
    SDL_QueryTexture(cancel, NULL, NULL, &textRect.w, &textRect.h);

    // draw
    SDL_RenderCopy(renderer, cancel, NULL, &textRect);
}
