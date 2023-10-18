#include "Puzzles.h"

// implementation is where the full function implementation sits

int puzzle1()
{
	cout << "Puzzle1! What is 7 + 2?" << endl;
	int num;
	cin >> num;

	if (num == 9)
	{
		cout << "Correct!" << endl;
		return 0;
	}

	else
	{
		cout << "Incorrect!" << endl;
		return 9;
	}
}

int puzzle2(int x, int y)
{
	cout << "Puzzle 2! What is " << x << " + " << y << " ? " << endl;
	int num;

	cin >> num;

	if (num == x + y)
	{
		cout << "Correct!" << endl;
		return 0;
	}
	else
	{
		cout << "Incorrect!" << endl;
		return 15;
	}
}

int puzzle3(string name)
{
	cout << "Puzzle3! What is your name? " << endl;
	string n;
	cin >> n;

	if (n == name)
	{
		cout << "Correct!" << endl;
		return 0;
	}

	else
	{
		cout << "Incorrect!" << endl;
		return 25;
	}
}