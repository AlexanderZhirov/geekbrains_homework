#include "parse_args.hpp"

[[ noreturn ]] void ra::print_usage_and_exit(int code)
{
	puts("Использование: lesson_8 [option] [arguments] ...\n");
	puts("  -h,  --help                               Получить информацию об использовании");
	puts("  -s,  --size        <count columns>        Размер сетки N*N");
	puts("  -w,  --width       <size>                 Ширина/высота игрового окна");
	puts("  -m,  --margin      <size>                 Размер внутреннего отступа от границы окна до игрового поля");
	exit(code);
}

void ra::parse_args(int argc, char *argv[], key **keys)
{
	int next_option = 0;

	do{
		next_option = getopt_long(argc, argv, short_options, long_options, nullptr);

		switch(next_option)
		{
			case 's':
				ra::get_argument(keys[ksize]);
				break;
			case 'w':
				ra::get_argument(keys[kwidth]);
				break;
			case 'm':
				ra::get_argument(keys[kmargin]);
				break;
			case 'h':
				ra::print_usage_and_exit(0);
				break;
			case '?':
				ra::print_usage_and_exit(1);
				break;
		}
	} while (next_option != -1);
}

void ra::get_argument(key *curKey)
{
	if (curKey->isset)
		ra::print_usage_and_exit(3);

	curKey->arguments[0] = optarg;
	curKey->isset = true;
	curKey->count = 1;
}
