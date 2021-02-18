#include <iostream>
#include <cstring>

// Задание 1
#define IN_THE_RANGE(num, max) ((num) >= 0 && (num) < (max))
// Задание 2
#define SIZE_INNER_ARRAY 20
#define SIZE_OUTER_ARRAY 5
#define GET_ELEMENT(array, row, col) (*(*((array) + (row)) + (col)))
// Задание 3
#define GET_SIZE_ARRAY(array, type) (sizeof(array) / sizeof(type))

int main()
{
	// Задание 1
	std::cout << IN_THE_RANGE(4, 11) << std::endl;            // 1
	std::cout << IN_THE_RANGE(0, 11) << std::endl;            // 1
	std::cout << IN_THE_RANGE(11, 11) << std::endl;           // 0
	std::cout << IN_THE_RANGE(2 + 3, 10 - 2) << std::endl;    // 1

	// Задание 2
	char **fullArray = (char **)malloc(sizeof(char *) * SIZE_OUTER_ARRAY);

	for (int i = 0; i < SIZE_OUTER_ARRAY; ++i)
		fullArray[i] = (char *)malloc(sizeof(char) * SIZE_INNER_ARRAY);

	// Рандомное заполнение
	strncpy(fullArray[2], "Hello friend!", 14);
	strncpy(fullArray[4], "My name is Alex.", 17);

	// Получаем доступ к 3-ей строке и 7-ой ячейке, что равно букве 'f'
	std::cout << GET_ELEMENT(fullArray, 2, 6) << std::endl;
	// Получаем доступ к 5-ой строке, т.к. ((0 + 3) + (2 - 1)) == 4,
	// и 16-ой ячейке ((2 * 7 + 1) == 15), что равно символу '.'
	std::cout << GET_ELEMENT(fullArray + 3, 2 - 1, 2 * 7 + 1) << std::endl;

	for (int i = 0; i < SIZE_OUTER_ARRAY; ++i)
		free(fullArray[i]);
	free(fullArray);

	// Задание 3
	float array[16];
	// Так как макрос заменит строку, то получается,
	// что sizeof() будет вызван локально, а не по ссылке в другой области видимости.
	// Таким образом и вычислим его размер. Хитро!:)
	std::cout << GET_SIZE_ARRAY(array, float) << std::endl;

	return 0;
}
