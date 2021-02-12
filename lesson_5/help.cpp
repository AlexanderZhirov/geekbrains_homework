#include "help.hpp"
#include <iostream>

void help::printArray(int *array, int size)
{
	for (int i = 0; i < size; ++i)
		std::cout << array[i] << ' ';
	std::cout << std::endl;
}

void help::printArray2(int *arraysSizes, int count, ...)
{
	std::va_list args;
	va_start(args, count);
	for (int i = 0; i < count; ++i) {
		int *array = va_arg(args, int *);
		std::cout << "Массив №" << i + 1 << ':' << std::endl;
		help::printArray(array, arraysSizes[i]);
	}
	va_end(args);
}
