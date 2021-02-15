#ifndef REALIZATION_HPP_
#define REALIZATION_HPP_

#include <fstream>
#include "parse_args.hpp"

char **generate_texts(int, int);
void free_texts(char **, int);
char **read_files(ra::key *);
int get_size_text(std::ifstream *);

#endif
