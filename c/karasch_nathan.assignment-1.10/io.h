#ifndef IO_H
# define IO_H

#include <string>

# define USAGE_STRING   "Usage: nb_parser <filename.txt>"
# define NB_SUBPATH     ".nextbus"

void usage();
void error(const char *message);
std::string get_file_contents(std::string &filepath);
std::string get_filepath(const char *filename);

#endif
