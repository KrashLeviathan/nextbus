#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "route_config_parser.h"

void usage() {
  std::cout << "Usage: nb_parser <filename.txt>" << std::endl;
}

void error(const char *message) {
  perror(message);
  exit(1);
}

void add_config_stop(std::ofstream &configFile,
		     const char *name,
		     const char *route,
		     const char *stop) {
  configFile << "$" << name << std::endl;
  configFile << "route=" << route << std::endl;
  configFile << "stop=" << stop << std::endl << std::endl;
}

bool init_config() {
  std::ofstream configFile;
  configFile.open("config.nextbus");
  if (configFile.is_open()) {
    configFile << "# NextBus Configuration File" << std::endl << std::endl;
    add_config_stop(configFile, "home",   "2E", "1123");
    add_config_stop(configFile, "school", "2W", "1077");
  configFile.close();
  return true;
  }
  return false;
}

std::string get_filepath(int argc, char **argv) {
  std::string filepath;
  std::string filename;
  char *path;
  
  if (argc != 2) {
    filename = "routeConfig.xml";
  } else {
    filename = argv[1];
  }

  path = getenv("HOME");
  if (path == NULL) {
    error("$HOME environment variable not found.");
  }
    
  filepath += path;
  filepath += "/.nextbus/";
  filepath += filename;

  return filepath;
}

int main(int argc, char *argv[]) {
  std::string filepath;
  std::string textToParse;

  // Test filepath setting
  filepath = get_filepath(argc, argv);
  std::cout << filepath << std::endl;

  // Test RouteConfigParser creation
  textToParse += "text to parse";
  RouteConfigParser parser (textToParse);
  std::string *voidPointer;
  voidPointer = static_cast<std::string *>(parser.next("Type of object"));
  std::cout << *voidPointer << std::endl;

  return 0;
}
