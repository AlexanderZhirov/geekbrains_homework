#include "exercise_3.hpp"

bool exercises::isLeftEqualRightSide(int *array, int size)
{
	int totalAmount = 0, leftSide = 0;

	for (int i = 0; i < size; ++i)
		totalAmount += array[i];

	for (int i = 0; i < size; ++i)
	{
		leftSide += array[i];
		if (leftSide == totalAmount - leftSide)
			return true;
	}

	return false;
}
