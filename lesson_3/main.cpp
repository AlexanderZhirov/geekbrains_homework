#include <iostream>

using namespace std;

extern const int aE, bE, cE, dE;

int main()
{
	// Задание 1
	const int a = 8, b = 7, c = 10, d = 3;
	float e;
	e = a * (b + (static_cast<float>(c) / d));
	cout << e << endl;
	// ИЛИ
	float f = c;
	e = a * (b + (f / d));
	cout << e << endl;

	// Задание 2
	int num = 0;
	cout << "Введите число: ";
	cin >> num;
	cout << ((num > 21) ? (num - 21) * 2 : 21 - num) << endl;

	// Задание 3
	e = aE * (bE + (static_cast<float>(cE) / dE));
	cout << e << endl;

	// Задание 4
	int array[3][3][3] =
	{
			{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
			{{10, 11, 12}, {13, 14, 15}, {16, 17, 18}},
			{{19, 20, 21}, {22, 23, 24}, {25, 26, 27}},
	};

	cout << "Вывод 1[*(*(array + 1) + 1)] == " << 1[*(*(array + 1) + 1)] << endl; // Этот вывод знаком из практики по Си
	cout << "Вывод *(*(*(array + 1) + 1) + 1) == " << *(*(*(array + 1) + 1) + 1) << endl;
	cout << "Вывод (*(*(array + 1) + 1))[1] == " << (*(*(array + 1) + 1))[1] << endl;

	return 0;
}
