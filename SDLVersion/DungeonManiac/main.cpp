// extra library includes

#include <iostream> // input and output stream
#include <string>
#include "Puzzles.h"


// Character includes
#include "Character.h"
#include "Hero.h"
#include "Mimic.h"
#include "Glob.h"
#include "MapScreen.h"


// SDL Libraries
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


// #include "Pangolin.h"
// #include "Animal.h"
// #include "Narwhal.h"

using namespace std; // a place to store variables



//void doBackFlip()
//{
//	cout << " Lets do this..." << endl;
//	cout << "Back flip" << endl;
//	cout << "and stick the landing ;)" << endl;
//}
//
//// expecting a double to be returned
//double workOutPi()
//{
//	double pi = 3.14159;
//
//	return pi;
//}
//
//// parameters
//float add(float x, float y)
//{
//	float sum = x + y;
//
//	return sum;
//}

int main(int argc, char** argv)
{
	// all of our starter code will start here


	//output hello world to the screen
	// cout = console out
	cout << " Hello there..." << endl; // endl = end line
	cout << "What is your name?" << endl;

	// variable to hold name of user/player
	// format of declaring a variable: datatype variableName;

	string name;

	// read name into name variable from keyboard
	// cin = console in
	cin >> name;

	cout << "Welcome to the dungeon " << name << endl;

	cout << "How old are you? " << endl;
	int age; // declare an age
	cin >> age;
	cout <<  "So you are " << age << " years old!" << endl;

	cout << "What is your favorite number: " << endl;
	int favNum;
	cin >> favNum;

	cout << "Well you are now stuck in this dungeon for  " << favNum << " years! Maniac!" << endl;

	// working out the new age
	int newAge = age + favNum;

	cout << "Its time to escape before you turn " << newAge << " years old!" << endl;

	// output warning if they'll be 80 or order
	if (newAge >= 80)
	{
		cout << "You might not even live to this age" << endl;
	}

	// if favNum is equal to 64 then ouput messagehh
	if (favNum == 64)
	{
		cout << "Nice favorite number by the way!" << endl;
	}

	// hero stats
	int hp = 0, str = 0, def = 0, agi = 0;

	bool characterSetup = false;

	while (characterSetup == false)
	{
		cout << "What type of character are you?" << endl;

		cout << "1 - Beserker" << endl;
		cout << "2 - Buff Nut" << endl;
		cout << "3 - Speedy Ninja" << endl;
		int choice;

		cin >> choice;

		if (choice == 1)
		{
			hp = 40;
			str = 10;
			def = 2;
			agi = 3;
		}

		else if (choice == 2)
		{
			hp = 60;
			str = 4;
			def = 5;
			agi = 1;
		}

		else if (choice == 3)
		{
			hp = 30;
			str = 3;
			def = 1;
			agi = 10;
		}

		else
		{
			cout << "Invalid choice! try again" << endl;
		}

		if (choice >= 1 && choice <= 3)
		{
			characterSetup = true;
		}
	}
	
	cout << "Stats" << endl;
	cout << "hp: " << hp << endl;
	cout << "strength: " << str << endl;
	cout << "defense: " << def << endl;
	cout << "agility: " << agi << endl;

	cout << "The first gate is opening, counting down..." << endl;



	// setup - condition, incrementer/decrementer
	for (int i = 10; i >= 0; i--)
	{
		cout << i << "...." << endl;
	}

	// intro to functions
	cout << "In the first room stands a tall slender figure in a cloak. " << endl;
	cout << "Totally skull faced, he speaks: " << endl;
	cout << "I will ask you 3 questions with various punishments, if you get them wrong" << endl;

	int dmg = puzzle1() + puzzle2(str, agi) + puzzle3(name);

	hp = hp - dmg;
	cout << "You are inflicted " << dmg << " points of damage! Your HP is now " << hp << endl;

	// build an object of class type character
	Character testCharacter;
	testCharacter.setupStats(hp, str, def, agi);
	testCharacter.displayStats();

	Character testCharacter2;
	testCharacter2.setupStats(100, 40, 36, 40);
	testCharacter2.displayStats();

	Hero hero;
	hero.setName(name);
	hero.setupStats(hp, str, def, agi);

	Glob glob1; // calls the constructor and fills in the base stats

	hero.takeDamage(glob1.getDamage());
	glob1.takeDamage(hero.getDamage());

	hero.displayStats();
	glob1.displayStats();
	glob1.makeDumbNoise();

	// class object pointers
	Glob* globPtr = new Glob();
	// (*globPtr).displayStats(); // same way as below

	globPtr->takeDamage(50);
	globPtr->displayStats();
	globPtr->makeDumbNoise();


	delete globPtr; // destroys the new Glob it is pointing at 
	globPtr = NULL;

	if (globPtr != NULL)
	{
		cout << "glob ptr pointing to something" << endl;
	}

	else
	{
		cout << "glob is dead!!!!" << endl;
	}

	/*int* wateva = new int;
	*wateva = 22;
	cout << "Wateva = " << *wateva << " wateva"*/

	// Polymorphism

	// reference as glob as the character(treat child like a parent)
	Character* charPtr = &glob1; // can do this since glob is a child type of the character
	charPtr->takeDamage(-10);
	charPtr->displayStats(); // access character type functions inside glob but not make dumb noises


	// casting - rereference child type as another type in the family tree
	Glob* globPtr2 = (Glob*)charPtr;
	globPtr2->makeDumbNoise();

	// Intialize SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		// if init not return 0, then initialization failed
		cout << "SDL Init Error: " << SDL_GetError() << endl;
		system("pause");
		return 1;
	}

	// Initialize subsytems we need e.g sdl image, mixer, ttf
	// TODO: Lookup C++ bitwise logic

	// image - being able to deal with other image types other than bmp. Also lets you play with surface pixel data
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		// if init not return 0, then initialization failed
		cout << "SDL IMG Init Error: " << IMG_GetError() << endl;
		system("pause");
		return 1;
	}

	// ttf - Text to Font for rendering text to screen
	if (TTF_Init() != 0)
	{
		// if init not return 0, then initialization failed
		cout << "SDL TTF Init Error: " << TTF_GetError() << endl;
		system("pause");
		return 1;
	}

	// Mixer - sound and music
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		cout << "SDL Mixer Init Error: " << Mix_GetError() << endl;
		system("pause");
		return 1;
	}



	// TODO Initialize image, mixer, ttf

	SDL_Window* window = SDL_CreateWindow("Dungeon Maniac!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		// if init not return 0, then initialization failed
		cout << "SDL Init Error: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
	{
		// if init not return 0, then initialization failed
		cout << "SDL renderer Error: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}

	// the size graphics are at min, but then scale up to actual window size
	SDL_RenderSetLogicalSize(renderer, 320, 240);


	// load up file abd store as texture inside the gfx card vram
	SDL_Texture* testImage = IMG_LoadTexture(renderer, "assets/girlIdle.png");

	if (testImage == NULL)
	{
		cout << "Image did not load!" << IMG_GetError() << endl;
	}

	// ITEMS(using arrays....)
	// items as ints, 0 = no item, 1 = Vanilla, 2 = grenade, 3 = attack up, 4 = defense up
	// integer array holding an array of 10 int variables
	int items[10];

	// loop through the array using for loop and set each slot to = 0 (no item)
	for (int i = 0; i <= 9; i++)
	{
		// can reference index using variable
		items[i] = 0;

	}

	// set first item slot (index 0) to be our int number representating a vanilla
	items[0] = 1;
	/*items[1] = 1;
	items[2] = 3;*/

	// cout << "items[0] = " << items[0] << endl;
	for (int i = 0; i <= 9; i++)
	{
		// can reference index using variable
		cout << "items [" << i << "] = " << items[i] << endl;

	}

	
	/*items[4] = 0;
	items[5] = 0;
	items[6] = 0;
	items[7] = 0;*/


	/*int item1 = 0;
	int item2 = 1;*/


	// setup mapscreen object
	// arrays don't need memory adresses they are addresed by default that's why items don't need memory adress
	MapScreen mapScreen(renderer, &hero, items);


	bool keepLooping = true;
	// game loop

	while (keepLooping)
	{
		SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255); // RGB (example R = 0-255)

		// clear entire screen with current draw color
		SDL_RenderClear(renderer);

		SDL_Rect rect;
		rect.x = 10;
		rect.y = 10;
		rect.w = 50;
		rect.h = 50;
		SDL_SetRenderDrawColor(renderer, 34, 76, 22, 255);

		// draws filled in rectangle to window using rectangles data
		SDL_RenderFillRect(renderer, &rect);

		// renderCopy renders textures to the window
		// SDL_RenderCopy(renderer, testImage, NULL, NULL);

		// the region of the texture we want draw from
		SDL_Rect srcRect;

		srcRect.x = 20;
		srcRect.y = 50;
		srcRect.w = 55;
		srcRect.h = 75;

		// texture destination rectangle
		SDL_Rect destReact;

		destReact.x = 70;
		destReact.y = 20;
		destReact.w = 107;
		destReact.h = 137;

		// renderCopy renders textures to the window
		SDL_RenderCopy(renderer, testImage, &srcRect, &destReact);

		// update mapscreen
		mapScreen.update();

		if (mapScreen.quit)
		{
			keepLooping = false;
		}


		// draw game world
		mapScreen.draw();

		// swaps drawing buffer
		SDL_RenderPresent(renderer);

		// ticks are milliseconds since start of SDL init
		//if (SDL_GetTicks() > 50300) // 1000ms = 1second
		//{
		//	keepLooping = false;
		//}

		

	}
	// cleanup
	SDL_DestroyTexture(testImage);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	
	// lets user interact by pressing anykey
	system("pause");
	return 0;

	
	// --- Fundamentals ---
	// --- variables --- 

	//int y = 5;
	//int x = y + 1;
	//cout << " x = " << x << endl;

	//y = 27 + x;

	//cout << "y = " << y << endl;
	//cout << " x = " << x << endl;

	//x = x + x;

	//cout << "x = " << endl;

	//// float - floating point, up to 7 decimal deep
	//float a = 3.34544;

	//cout << " a = " << a << endl;

	//// double - decimal up to 15 decimals deep
	//double b = 3.232343242344234;
	//cout << " b = " << b << endl;

	//// bool = boolean, true or false
	//bool t = true;

	//cout << "t = " << t << endl;


	//// char = character, represents 1 character (includes non-printable characters)
	//char l = '#';

	//cout << "l = " << l << endl;


	//// String = string of characters, useful for names, addresses sentences, etc
	//string sentence = "I like chocolate! ";
	//cout << "sentence =" << sentence << endl;

	//// rules of variable name

	//// must start with a letter or underscore
	//// no spaces or special characters
	//// can contain numbers but not at the start
	//// letters, underscores, and numbers (but not at start)


	//int my_name_is_maniac;
	//// int 234sdfsdf; can't do it

	//int _hello;

	//// common standardm camel casing

	//int myNameIsManiac;

	//bool destroyEvidence = true;
	//destroyEvidence = false;

	// ---  math ----

	//int x = 5 + 2;
	//cout << " x = " << x << endl;

	//x = 2 + 5 * 10; //* = multiply
	//cout << " x = " << x << endl;

	//x = (2 + 5) * 10;
	//cout << " x = " << x << endl;

	//int y = x / 10; // / is division
	//cout << "y = " << y << endl;

	//int z = 5 % 2; //% = modulus modulus (give remainder in whole number after dividing 5 by 2 evenly)

	//cout << "z = " << z << endl;
	//int a = x + y + z;

	//cout << "a = " << a << endl;

	//// integer division, cuts off decimal values, does not round up or down
	//int intDiv = 5 / 2;
	//cout << "intDiv = " << intDiv << endl;

	//float floatDiv = 5 / 2;
	//cout << "floatDiv = " << floatDiv << endl;

	//a = a + 2;
	//cout << " a = " << a << endl;

	//// shorthand if re-using variables original value

	//a += 2;

	//cout << " a = " << a << endl;

	//// for adding 1 or subtracting 1 
	//a++; // adds 1

	//cout << "a = " << a << endl;
	//a--; // takes 1 away

	//cout << "a = " << a << endl;

	// If statements
	//cout << "How old are you?";
	//int age2 = 0;
	//cin >> age2;

	//// if statements - great for branching code
	///*
	//	> greater than
	//	>= greater than or equal to
	//	< less than
	//	<= less than
	//	== does value on left equal to the value on right
	//	!= does not equal
	//	! flips the answer
	//
	//*/

	//// && - and
	//// and equates to true only if expressions on the left and right are met (are true)

	//// if your age is not zero
	//if (age != 0)
	//{
	//	cout << " You are not a new born baby" << endl;
	//}

	//else
	//{
	//	cout << "You are a tiny baby" << endl;
	//}

	//// if you are not aged between 4 and 9
	//if (!(age > 3 && age < 10))
	//{
	//	cout << " You are not a kid!!!" << endl;
	//}


	//if (age2 > 66)
	//{
	//	// in the event age is greater than 66, output message
	//	cout << " damn! you old!" << endl;
	//}

	//else if (age2 > 3 && age2 < 10)
	//{
	//	cout << "damn! you to young" << endl;

	//}

	//else
	//{
	//	// if not old, then do this
	//	cout << "You are not old!" << endl;
	//}

	//// if and AND
	//bool boughtPizza = true;
	//bool boughtDrink = false;

//
//// || or
//// if expressions is met (true) on either side, then or equates to true
//// or can only be false if both conditions are not met


//if (boughtPizza == true && boughtDrink == true)
//{
//	cout << "You get a discount" << endl;
//}

//else
//{
//	cout << "No discount for you!!" << endl;
//}

//// if and OR
//if (boughtPizza == true || boughtDrink == true)
//{
//	cout << "You geta mega discount" << endl;
//}
//else
//{
//	cout << "no mega discount for you !!!" << endl;
//}

//// if older than 70 and bought something

//if (age2 >= 70 && (boughtPizza || boughtDrink))
//{
//	cout << "congrats you get heart disease" << endl;
//}

//else
//{
//	cout << "You are either young or foodless" << endl;
//}

// while loops

/*bool eatenLunch = false;

while (eatenLunch == false)
{
	cout << "Eat Lunch now? y / n" << endl;
	char choice;
	cin >> choice;
	if (choice == 'y')
	{
		eatenLunch = true;
	}

}

cout << "Yay Lunch" << endl;

int moneyTotal = 0;

while (moneyTotal < 100000)
{
	cout << "This is a mugging! give me all your cash! Enter in cash amount: " << endl;
	int cash;
	cin >> cash;

	moneyTotal = moneyTotal + cash;

	cout << "Total so far is: $" << moneyTotal << endl;

	if (cash < 0)
	{
		cout << "You just mugged the mugger!" << endl;
		break;
	}
}

cout << "Mugger buys a mercedes and escapes" << endl;*/

// For loops

// increment using while loops
//int i = 1;
//while (i <= 10)
//{
//	cout << i << endl;
//	i++;
//}

//// increment using for loops
//cout << "for loop" << endl;

//for (int f = 1; f <= 10; f++)
//{
//	cout << f << endl;
//}

// Functions

// structure:
// returnType functionName(parameter list)
//{
//	function body
//}

// reusable and can be modularized, test, easier to test and maintain and find bugs
	
	//double pi = workOutPi();
	//cout << "Pi is " << pi << endl;

	//// 234 and 43 are arguments and are copied into x and y
	//float a = add(234, 42);

	//cout << " a = " << a << endl;

	//float b = add(pi, pi);
	//cout << "b = " << b << endl;

	//float x = 22, y = 33;

	//// copy values from variable x into parameter x
	//// and variable y into parameter y
	//float c = add(x, y);
	//
	//cout << " c = " << c << endl;

	//float z = add(a, b) + add(b, c) + workOutPi();

	//cout << "z = " << z << endl;

// ---- Classes ----
	
	// Instanciating object of type class pangolin
	//Pangolin p1;

	//
	//p1.setName("Jeff");

	//p1.setName("");


	//// cannot access private parts of the class through accessor
	//// p1.name = "geoff";
	//// can call or access public of our class through the dot(.) accessor
	//p1.antsEaten = 0; // initialize
	//
	//p1.eatAnts(12);
	//p1.eatAnts(52);
	//
	//
	//p1.displayStats();

	//Pangolin p2;
	//p2.setName("Jerk face");
	//p2.antsEaten = 0;

	//p2.eatAnts(p1.antsEaten);

	//p2.displayStats();

	//cout << p2.getName() << "is a jerk" << endl;

	//cout << "he ate all" << p2.antsEaten << " ants! " << endl;


	// ---- Pointers ----

	//int x = 2;

	//// & means get the memory address of the variable
	//cout << "&x = " << &x << endl;

	//// int pointer type
	//int* iPtr;
	//iPtr = &x;

	////means get the memory address of the variable
	//cout << "iPtr = " << iPtr << endl;

	//// * = dereference the pointer, go to the things value of what I am pointing at
	//*iPtr = 17;
	//cout << "x = " << x << endl;

	//cout << "*iPtr = " << *iPtr << endl;

	//int y = 666;
	//iPtr = &y;

	//cout << "iPtr = " << iPtr << endl;
	//cout << "*iPtr = " << *iPtr << endl;

	// --- Dynamic Memory ----
	
	//string* sPtr;
	//sPtr = new string();

	//*sPtr = "Bob";
	//cout << "sPtr = " << sPtr << endl;
	//cout << "*sPtr = " << *sPtr << endl;

	//// done with bob delete him
	//delete sPtr;
	//// note: pointer is still useful and still pointing to where bobs string was
	//// make sure not to try change values there
	//// *sPtr = "Jeff"; not Allowedm we don't have rights to this part of ram now

	//sPtr = NULL;
	//
	//if (sPtr != NULL)
	//{
	//	*sPtr = "Jeff";
	//}

	//sPtr = new string();
	//
	//*sPtr = "Jemima";

	//cout << "sPtr = " << sPtr << endl;
	//cout << "*sPtr = " << *sPtr << endl;

	//sPtr = new string();

	//// oh no, I didn't delete Jemima new string
	//// this is called a memory leak, we lost reference to Jemima and can't delete her
	//*sPtr = "Sab";

	//cout << "sPtr = " << sPtr << endl;
	//cout << "*sPtr = " << *sPtr << endl;

	//delete sPtr; // deleting Sab


	// --- Polymorphism ---
	//Animal a1("Jeff", 48);
	//a1.eat();
	//a1.makeSound();
	//a1.display();

	//Narwhal n1("Unicorn", 22, 2.1);
	//n1.eat();
	//n1.makeSound();
	//n1.display();
	//n1.swim();

	//Animal* aPtr = new Narwhal("Rhino", 3, 0.4);
	//aPtr->eat(); // runs narwhals version of eat if eat is virtual on animal class
	//aPtr->makeSound();
	//aPtr->display();

	


	// lets the user interact with anything
	// system("pause");
}