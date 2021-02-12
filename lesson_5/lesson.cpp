#include <iostream>
#include "lesson.hpp"
#include "help.hpp"
#include "exercise_1.hpp"
#include "exercise_2.hpp"
#include "exercise_3.hpp"
#include "exercise_4.hpp"
#include "exercise_5.hpp"

namespace lesson
{
	void (*printArray)(int *, int) = help::printArray;
	void (*printArray2)(int *, int, ...) = help::printArray2;

	void exercise_1()
	{
		void (*changeArray)(int *, int) = exercises::changeArray;

		int size = 10;
		int array[size] = {1, 1, 0, 0, 1, 0, 1, 1, 0, 0};

		std::cout << "********** Задание 1 **********" << std::endl;

		printArray(array, size);
		changeArray(array, size);
		printArray(array, size);
	}

	void exercise_2()
	{
		void (*fillArray)(int *, int) = exercises::fillArray;

		int size = 8;
		int array[size] = {0};

		std::cout << "********** Задание 2 **********" << std::endl;

		printArray(array, size);
		fillArray(array, size);
		printArray(array, size);
	}

	void exercise_3()
	{
		bool (*isLeftEqualRightSide)(int*, int) = exercises::isLeftEqualRightSide;

		int size = 5;
		int array[3][size] =
		{
				{1, 1, 1, 2, 1},
				{2, 1, 1, 2, 1},
				{10, 1, 2, 3, 4},
		};

		std::cout << "********** Задание 3 **********" << std::endl;

		for (int i = 0; i < 3; ++i)
		{
			printArray(array[i], size);

			std::cout << "В массиве " << ((isLeftEqualRightSide(array[i], size)) ? "есть" : "отсутствует") << " место, в котором сумма левой и правой части массива равны" << std::endl;

		}
	}

	void exercise_4()
	{
		void (*offsetElements)(int*, int, int) = exercises::offsetElements;

		int size = 10, offset = 0;
		int array[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		std::cout << "********** Задание 4 **********" << std::endl;
		std::cout << "Введите смещение: ";
		std::cin >> offset;

		printArray(array, size);
		offsetElements(array, size, offset);
		printArray(array, size);
	}

	void exercise_5()
	{
		void (*changeArray2)(int *, int, ...) = exercises::changeArray2;

		int count = 2;
		int arraysSizes[count] = {10, 7};
		int array1[10] = {1, 1, 0, 0, 1, 0, 1, 1, 0, 0};
		int array2[7] = {0, 1, 1, 1, 1, 0, 1};

		std::cout << "********** Задание 5 **********" << std::endl;

		std::cout << "До изменения:" << std::endl;
		printArray2(arraysSizes, count, array1, array2);
		changeArray2(arraysSizes, count, array1, array2);
		std::cout << "После изменения:" << std::endl;
		printArray2(arraysSizes, count, array1, array2);
	}
}
