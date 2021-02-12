#include "exercise_4.hpp"
#include <cmath>
#include <iostream>

// Получить наибольший общий делитель для bigNum и smallNum
int exercises::commonDivisor(int bigNum, int smallNum)
{
	while (smallNum != 0)
	{
		int remainder = bigNum % smallNum;
		bigNum = smallNum;
		smallNum = remainder;
	}

	return bigNum;
}

void exercises::offsetElements(int *array, int size, int offset)
{
	int firstItemIndex = 0;

	offset %= size;
	if (offset == 0)
		return;
	if (offset < 0)
		offset += size;

	int divisor = exercises::commonDivisor(size, offset);

	while (firstItemIndex < divisor)
	{
		int lastItemIndex = firstItemIndex - offset;
		if (lastItemIndex < 0)
			lastItemIndex += size;

		int tempValue = array[lastItemIndex];

		while (lastItemIndex != firstItemIndex)
		{
			int previousItemIndexToLast = lastItemIndex - offset;

			if (previousItemIndexToLast < 0)
				previousItemIndexToLast += size;

			array[lastItemIndex] = array[previousItemIndexToLast];

			lastItemIndex = previousItemIndexToLast;
		}

		array[firstItemIndex] = tempValue;
		++firstItemIndex;
	}
}
