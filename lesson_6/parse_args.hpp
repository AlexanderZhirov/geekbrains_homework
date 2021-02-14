#ifndef PARSE_ARGS_HPP_
#define PARSE_ARGS_HPP_

#include <iostream>
#include <getopt.h>

namespace ra // read arguments
{
	enum keys {input, output};

	typedef struct
	{
		bool required = false;				// Ключ является обязательным для установки
		bool isset = false;					// Был установлен при запуске программы
		int count = 0;						// Количество аргументов переданных для текущего ключа
		char *arguments[10] = {nullptr};	// Переданные аргументы (до 10 аругментов на один ключ)
	} key;

	const char* const short_options = "hi:o:";

	const struct option long_options[] =
	{
		{ "help", 0, nullptr, 'h'},
		{ "input", 1, nullptr, 'i'},
		{ "output", 1, nullptr, 'o'},
		{ nullptr, 0, nullptr, 0}
	};

	[[ noreturn ]] void print_usage_and_exit(int);
	void parse_args(int, char **, key **);
	void get_full_parameters(int, char **, key *);
	void check_parameters(key **, int);
}

#endif
