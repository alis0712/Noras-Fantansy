#include "cleanup.h"
#include "res_path.h"
#include "drawing_functions.h"
#include <SDL_mixer.h>
#include "globals.h"
#include "game.h"

// random numbers and time libraries
#include <cstdlib> // srand , rand
#include <ctime> // time 



int main(int argc, char** argv)
{
	// set the random seed for the random number sequence
	srand(time(0)); // this generates a random sequence of random numbers, very useful for games like splunky for procederal maps, get a random number series everytime

	// rand()%10 + 1; // 0-234244, gives numbers between 1-10, definitely help for enemies, // we tend to work with smaller numbers








	// setup SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "error initializing SDL" << endl;
		return 1;
	}

	// setup window
	SDL_Window* window = SDL_CreateWindow("Nora's Fantasy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		Globals::ScreenWidth*Globals::ScreenScale, Globals::ScreenHeight * Globals::ScreenScale, SDL_WINDOW_SHOWN);
	
	// For full screen mode SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN

	if (window == nullptr)
	{
		SDL_Quit();
		cout << "Window Error" << endl;
		return 1;
	}

	// setup renderer
	Globals::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (Globals::renderer == nullptr)
	{
		cleanup(window);
		SDL_Quit();
		cout << "renderer error" << endl;
		return 1;
	}

	// This is the size to draw things at, before we scale it to the screen size dimensions mentioned in createWindow
	SDL_RenderSetLogicalSize(Globals::renderer, Globals::ScreenWidth, Globals::ScreenHeight);
	
	// Initialize SDL_Image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_Quit();
		cout << "sdl image didn't initialize" << endl;
	}

	// initialize text to font
	if (TTF_Init() != 0)
	{
		SDL_Quit();
		cout << "SDL ttf didn't initialize" << endl;
		return 1;
	}

	// initialize sdl mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		SDL_Quit();
		cout << "Mixer didn't initialize" << endl;
		return 1;
	}

	// load up a texture to draw
	//string resPath = getResourcePath();
	//SDL_Texture* texture = loadTexture(resPath + "map.png", Globals::renderer);

	//// run game for 5000 ticks (5000ms)

	//while (SDL_GetTicks() < 5000)
	//{
	//	// clear the screen
	//	SDL_RenderClear(Globals::renderer);

	//	// draw what we want next to the screen
	//	renderTexture(texture, Globals::renderer, 0, 0);

	//	// show image we have been rendering
	//	SDL_RenderPresent(Globals::renderer);
	//}

	Game game;
	game.update();

	cleanup(Globals::renderer);
	cleanup(window);
	// cleanup(texture);

	SDL_Quit();
	return 0;
}