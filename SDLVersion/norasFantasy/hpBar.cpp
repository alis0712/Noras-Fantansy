#include "hpBar.h"

void HPBar::draw(const SDL_Color& color)
{
	if (entity != NULL)
	{
		// SDL_SetRenderDrawColor(Globals::renderer, 240, 51, 159, SDL_ALPHA_OPAQUE);

		SDL_SetRenderDrawColor(Globals::renderer, color.r, color.g, color.b, color.a);

		// draw outside of hp bar
		SDL_Rect barContainer = { x, y, barWidth, barHeight };

		// rectangle outline of 1 pixel
		SDL_RenderDrawRect(Globals::renderer, &barContainer);

		// percentage of entities health remaining, 1 as 100% or 0.5 as 50%
		float hpPercent = entity->hp / (entity->hpMax * 1.0f); // to make sure nothing doesn't get chopped, upgrade math into float division so that we don't lose decimals

		// example 50/100 = 0.5 but in integer division, removes decimal, so we get 0

		SDL_Rect hpRect = { x + 2, y + 2, (barWidth - 4) * hpPercent, barHeight - 4 }; // how tall it is going to be, two pixels on each side, move by how boss has health

		SDL_RenderFillRect(Globals::renderer, &hpRect);

	}

}
