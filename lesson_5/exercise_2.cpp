#include "exercise_2.hpp"

void exercises::fillArray(int *array, int size)
{
	array[0] = 1;

	for (int i = 1; i < size; ++i)
		array[i] = array[i - 1] + 3;
}
