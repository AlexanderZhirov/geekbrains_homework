#include <iostream>
#include <fstream>
#include <cstring>
#include "parse_args.hpp"
#include "realization.hpp"

using namespace std;

int main(int argc, char **argv)
{
	int countKeys = 5;

	ra::key kg;  // generate
	ra::key kS;  // size
	ra::key kc;  // count
	ra::key ki;  // input
	ra::key ks;  // search
	ra::key ko;  // output

	ra::key *keys[countKeys] = {&kg, &kS, &kc, &ki, &ks, &ko};

	ra::parse_args(argc, argv, keys);

	if ((kg.isset && ki.isset) || (!kg.isset && !ki.isset))
		ra::print_usage_and_exit(10);

	if (kg.isset && kS.isset && kc.isset && !ks.isset)
	{
		if (ko.isset && ko.count != atoi(kc.arguments[0]))
			ra::print_usage_and_exit(11);

		if (ki.isset && ko.isset && ko.count > 1)
			ra::print_usage_and_exit(12);

		char **texts = generate_texts(atoi(kS.arguments[0]), atoi(kc.arguments[0]));

		if (ko.isset)
		{
			for (int i = 0; i < ko.count; ++i)
			{
				ofstream ofile(ko.arguments[i]);
				ofile << texts[i] << '\n';
			}
		}
		else
		{
			for (int i = 0; i < atoi(kc.arguments[0]); ++i)
			{
				cout << texts[i] << endl;
			}
		}

		free_texts(texts, atoi(kc.arguments[0]));
	}
	else if (ki.isset && !kS.isset && !kc.isset)
	{
		char **texts = read_files(&ki);

		if (ks.isset)
		{
			bool found = false;

			for (int i = 0; i < ki.count; ++i)
			{
				if (strstr(texts[i], ks.arguments[0]))
				{
					cout << "Строка \"" << ks.arguments[0] << "\" присутствует в файле " << ki.arguments[i] << endl;
					if (!found)
						found = true;
				}
			}

			if (!found)
				cout << "Не удалось найти строку \"" << ks.arguments[0] << "\"" << endl;
		}

		if (ko.isset)
		{
			ofstream ofile(ko.arguments[0]);

			for (int i = 0; i < ki.count; ++i)
				ofile << texts[i];

			ofile << '\n';
		}

		free_texts(texts, ki.count);
	}
	else
		ra::print_usage_and_exit(13);

	return 0;
}
