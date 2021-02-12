#include "exercise_1.hpp"

void exercises::changeArray(int *array, int size)
{
	for (int i = 0; i < size; ++i)
		array[i] = !array[i];
}
