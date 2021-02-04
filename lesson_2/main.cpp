#include <iostream>

using namespace std;

int main()
{
	// Задание 1
	int a = 4;
	float b = 3.2;
	char c = 'a';
	bool d = true;

	// Задание 2
	enum valueTicTacToe {clean, x, o};

	// Задание 3
	valueTicTacToe map[3][3] = {clean};

	// Задание 4
	struct ticTacToe
	{
		valueTicTacToe map[3][3];
		valueTicTacToe current;
		bool endGame;
		unsigned int countMove;
	};

	// Задание 5
	struct curQuantity
	{
		union quanity
		{
			short count;
			float weight;
			float volume;
		};
		int count : 1;
		int pounds : 1;
		int pints : 1;
	};

	return 0;
}
