#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>

#include "io.h"

struct stat sb;

void usage() {
  std::cout << USAGE_STRING << std::endl;
}

void error(const char *message) {
  perror(message);
  exit(1);
}

std::string get_file_contents(std::string &filepath) {
  std::ifstream file;
  std::stringstream contents;
  std::string line;

  file.open(filepath.c_str());
  if (file.is_open()) {
    while ( getline (file,line) ){
      contents << line << std::endl;
    }
    file.close();
  } else {
    contents << filepath << " could not be opened.";
  }
  return contents.str();
}

std::string get_filepath(const char *filename) {
  std::string filepath;
  char *path;
  
  path = getenv("HOME");
  if (path == NULL) {
    error("get_filepath");
  }
  filepath += path;
  filepath += "/" NB_SUBPATH "/";
  // Check to see if the .nextbus directory exists, and create it
  // if it doesn't.
  if (!(stat(filepath.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) {
    system("mkdir -v $HOME/" NB_SUBPATH);
  }
  filepath += filename;
  return filepath;
}
