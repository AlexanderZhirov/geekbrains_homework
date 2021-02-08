#include <iostream>

using namespace std;

void exercise_1();
void exercise_2();
void exercise_3();
void exercise_4();

bool isPrime(unsigned int);
bool isLeapYear(unsigned short);

int main()
{
	exercise_1();
	exercise_2();
	exercise_3();
	exercise_4();

	return 0;
}

void exercise_1()
{
	int a = 0, b = 0, c = 0;
	cout << "********** Задание 1 **********" << endl;
	cout << "Введите первое число: ";
	cin >> a;
	cout << "Введите второе число: ";
	cin >> b;
	c = a + b;
	if (c >= 10 && c <= 20)
		cout << true << endl;
	else
		cout << false << endl;
}

void exercise_2()
{
	unsigned int a;
	cout << "********** Задание 2 **********" << endl;
	cout << "Введите целое число: ";
	cin >> a;
	cout << (isPrime(a) ? "Число является простым" : "Число не простое") << endl;
}

void exercise_3()
{
	const int a = 11, b = 7;
	cout << "********** Задание 3 **********" << endl;
	if ((a == 10 && b == 10) || a + b == 10)
		cout << true << endl;
	else
		cout << false << endl;
}

void exercise_4()
{
	unsigned short year = 0;
	cout << "********** Задание 4 **********" << endl;
	cout << "Введите год: ";
	cin >> year;
	cout << (isLeapYear(year) ? "Год является високосным" : "Год не високосный") << endl;
}

bool isPrime(unsigned int num)
{
	unsigned int limit = num / 2;

	if (num > 2)
	{
		for (unsigned int i = 2; i < num; ++i)
		{
			if (num % i == 0)
				return false;
			if (i == limit)
				break;
		}
	}

	return true;
}

bool isLeapYear(unsigned short year)
{
	if (year % 4 == 0 && (year % 400 == 0 || year % 100 != 0))
		return true;

	return false;
}
