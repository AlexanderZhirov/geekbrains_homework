#include "exercise_1.hpp"
#include "exercise_5.hpp"

void exercises::changeArray2(int *arraysSizes, int count, ...)
{
	std::va_list args;
	va_start(args, count);
	for (int i = 0; i < count; ++i) {
		int *array = va_arg(args, int *);
		exercises::changeArray(array, arraysSizes[i]);
	}
	va_end(args);
}
