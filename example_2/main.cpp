#include <iostream>
#include "parse_args.hpp"

using namespace std;

int main(int argc, char **argv)
{
	int countKeys = 2;

	ra::key ifile = {.required = true};
	ra::key ofile;

	ra::key *keys[countKeys] = {&ifile, &ofile};

	ra::parse_args(argc, argv, keys);
	ra::check_keys(keys, countKeys);

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < keys[i]->count; ++j)
		{
			cout << i << ' ' << keys[i]->arguments[j] << ' ';
		}
		cout << endl;
	}

	return 0;
}
