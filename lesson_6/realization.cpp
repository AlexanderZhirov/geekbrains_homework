#include "realization.hpp"
#include <random>
#include <cstdlib>

char **generate_texts(int size, int count)
{
	std::random_device rd;
	std::mt19937_64 mersenne(rd());

	char **texts = (char **)malloc(sizeof(char *) * count);

	if (!texts)
		exit(20);

	for (int i = 0; i < count; ++i)
	{
		char *text = (char *)malloc(sizeof(char) * size + 1); // +1 это символ '\0'

		if (!text)
			exit(21);

		for (int j = 0; j < size; ++j)
			text[j] = ((mersenne() % 2) ? 65 : 97) + (mersenne() % 26);

		text[size] = '\0';
		texts[i] = text;
	}

	return texts;
}

void free_texts(char **texts, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (texts[i])
			free(texts[i]);
	}
	free(texts);
}

int get_size_text(std::ifstream *file)
{
	// Можно было бы считать количество байтов через перемещение каретки
	// seekg(0, ios::end); tellg();
	// Через get() считываем посимвольно

	int size = 0;
	char ch;

	while (*file)
	{
		file->get(ch);
		size++;
	}

	file->clear();              // Сбрасываем все флаги для повторного чтения
	file->seekg(0, std::ios::beg);   // Возвращаем каретку чтения на начало файла

	return size;
}

char **read_files(ra::key *files)
{
	char **texts = (char **)malloc(sizeof(char *) * files->count);

	if (!texts)
		exit(20);

	for (int i = 0; i < files->count; ++i)
	{
		std::ifstream ifile(files->arguments[i]);
		int curChar = 0;
		int size = get_size_text(&ifile);

		char *text = (char *)malloc(sizeof(char) * size);

		if (!text)
			exit(21);

		while (ifile)
			ifile.get(text[curChar++]);

		texts[i] = text;
	}

	return texts;
}
