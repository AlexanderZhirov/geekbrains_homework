#include <iostream>
#include <random>

using namespace std;

int remDiv(uint_fast64_t);

int main()
{
	random_device rd;
	mt19937_64 mersenne(rd());

	for (int i = 0; i < 5; i += remDiv(mersenne()))
	{
		cout << i << ' ';
	}

	return 0;
}

int remDiv(uint_fast64_t m)
{
	int num;

	num = m % 3;

	return num;
}
