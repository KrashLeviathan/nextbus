#include <fstream>
#include <string>
#include "config.h"

void add_config_stop(std::ofstream &configFile,
		     const char *name,
		     const char *route,
		     const char *stop) {
  configFile << "$" << name << std::endl;
  configFile << "route=" << route << std::endl;
  configFile << "stop=" << stop << std::endl << std::endl;
}

bool init_config(std::string &filepath) {
  std::ofstream configFile;
  configFile.open(filepath.c_str());
  if (configFile.is_open()) {
    configFile << "# NextBus Configuration File" << std::endl << std::endl;
    add_config_stop(configFile, "home",   "2E", "1123");
    add_config_stop(configFile, "school", "2W", "1077");
    configFile.close();
  return true;
  }
  return false;
}
