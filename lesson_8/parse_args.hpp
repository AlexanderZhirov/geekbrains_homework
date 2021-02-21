#ifndef PARSE_ARGS_HPP_
#define PARSE_ARGS_HPP_

#include <iostream>
#include <getopt.h>

namespace ra // read arguments
{
	enum keys {ksize, kwidth, kmargin};

	typedef struct
	{
		bool required = false;              // Ключ является обязательным для установки
		bool isset = false;                 // Ключ был установлен при запуске программы
		int count = 0;                      // Количество аргументов переданных для текущего ключа
		char *arguments[1] = {nullptr};    // Переданные аргументы (до 10 аругментов на один ключ)
	} key;

	const char* const short_options = "hs:w:m:";

	const struct option long_options[] =
	{
		{ "help", 0, nullptr, 'h'},
		{ "size", 1, nullptr, 's'},
		{ "width", 1, nullptr, 'w'},
		{ "margin", 1, nullptr, 'm'},
		{ nullptr, 0, nullptr, 0}
	};

	[[ noreturn ]] void print_usage_and_exit(int);    // Напечатать справку и выйти с кодом ошибки
	void parse_args(int, char **, key **);            // Прочитать все ключи
	void get_argument(key *);                         // Получить аргумент ключа
}



#endif
