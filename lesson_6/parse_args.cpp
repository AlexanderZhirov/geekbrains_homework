#include "parse_args.hpp"

[[ noreturn ]] void ra::print_usage_and_exit(int code)
{
	puts("Использование: lesson_6 [option] [arguments] ...\n");
	puts("  -h,  --help                 Получить информацию об использовании");
	puts("  -i,  --input   <file ...>   Указать файл(ы) для чтения");
	puts("  -o,  --output  <file>       Указать файл для записи");
	puts("                              Если файла не существует - будет создан новый\n");
	exit(code);
}

void ra::parse_args(int argc, char *argv[], key **keys)
{
	int next_option = 0;

	do{
		next_option = getopt_long(argc, argv, short_options, long_options, nullptr);

		switch(next_option)
		{
			case 'i':
				ra::get_full_parameters(argc, argv, keys[input]);
				break;
			case 'o':
				keys[output]->parameters[0] = optarg;
				keys[output]->isset = true;
				keys[output]->count = 1;
				break;
			case 'h':
				ra::print_usage_and_exit(0);
				break;
			case '?':
				ra::print_usage_and_exit(-1);
				break;
		}
	} while (next_option != -1);
}

void ra::get_full_parameters(int argc, char *argv[], key *curKey)
{
	int i = 0;

	if (curKey->isset)
		i = curKey->count;
	else
		curKey->isset = true;

	curKey->parameters[i++] = optarg;
	if (optind < argc)
	{
		while (optind < argc && *argv[optind] != '-')
		{
			curKey->parameters[i++] = argv[optind++];
		}
	}

	curKey->count = i;
}

void ra::check_parameters(key **keys, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (keys[i]->required && !keys[i]->isset)
			ra::print_usage_and_exit(-2);
	}
}













