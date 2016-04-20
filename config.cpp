#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "config.h"
#include "io.h"

#define CHECK_HEADING(str) \
    if (!getline(ss,line) || line.compare(str)) { \
    std::cout << "ERROR: " << line << std::endl; \
    return false; \
  }

void ConfigFile::print_details() {
  int i;
  std::cout << "Last Usage" << std::endl;
  std::cout << lastUsage << std::endl;
  std::cout << "Last Route DL" << std::endl;
  std::cout << lastRouteDownload << std::endl;
  std::cout << "Agency" << std::endl;
  std::cout << agency << std::endl;
  std::cout << "Saved" << std::endl;
  for (i = 0; i < savedRouteStops.size(); i++) {
    std::cout << savedRouteStops[i]->name << std::endl;
    std::cout << savedRouteStops[i]->route << std::endl;
    std::cout << savedRouteStops[i]->stop << std::endl;
  }
}

ConfigFile::ConfigFile(std::string &file_path) {
  filepath = file_path;
  contents = get_file_contents(filepath);
  if (!parse()) {
    // The contents were empty or invalid, so initialize
    // a new config file.
    std::cout
      << std::endl
      << "   If this is your first time running nextbus, this is normal!"
      << std::endl
      << "   Otherwise, it's possible your config.nextbus file was invalid"
      << std::endl
      << "   or corrupted. Use the command line arguments to change agency"
      << std::endl
      << "   or save routes/stops safely. If you want to edit the config"
      << std::endl
      << "   file manually, do so with caution!"
      << std::endl << std::endl
      << IO_GREEN "Creating a new config file at "
      << filepath << IO_NORMAL << std::endl << std::endl;
    lastUsage = 0;
    lastRouteDownload = 0;
    agency = DEFAULT_AGENCY;
    update();
  }
}

bool ConfigFile::update() {
  std::ofstream file;
  int i;
  
  file.open(filepath.c_str());
  if (file.is_open()) {
    file << CONFIG_HEADER << std::endl;
    file << "version " << VERSION_NUMBER << std::endl << std::endl;
    
    file << ":LAST USAGE" << std::endl;
    file << lastUsage << std::endl << std::endl;
    
    file << ":LAST ROUTE DOWNLOAD" << std::endl;
    file << lastRouteDownload << std::endl << std::endl;
    
    file << ":AGENCY" << std::endl;
    file << agency << std::endl << std::endl;

    file << ":SAVED" << std::endl;
    if (!savedRouteStops.empty()) {
      for (i = 0; i < savedRouteStops.size(); i++) {
	file << std::endl << "$" << savedRouteStops[i]->name << std::endl;
	file << "route=" << savedRouteStops[i]->route << std::endl;
	file << "stop=" << savedRouteStops[i]->stop << std::endl;
      }
    }
    file.close();
    return true;
  }
  return false;
}

bool ConfigFile::parse() {
  std::stringstream ss (contents);
  std::stringstream *stringToInt;
  std::string line;
  SavedRouteStop *savedRS;

  CHECK_HEADING(CONFIG_HEADER);
  CHECK_HEADING("version " VERSION_NUMBER);
  getline(ss, line);
  CHECK_HEADING(":LAST USAGE");
  getline(ss, line);
  stringToInt = new std::stringstream(line);
  *stringToInt >> lastUsage;
  delete stringToInt;
  getline(ss, line);
  CHECK_HEADING(":LAST ROUTE DOWNLOAD");
  getline(ss, line);
  stringToInt = new std::stringstream(line);
  *stringToInt >> lastRouteDownload;
  delete stringToInt;
  getline(ss, line);
  CHECK_HEADING(":AGENCY");
  getline(ss, line);
  agency = line;
  getline(ss, line);
  CHECK_HEADING(":SAVED");
  while (getline(ss, line)) {
    if (line.compare("")) {
      // If the line is not empty...
      savedRS = new SavedRouteStop();
      if (line[0] == '$') {
	savedRS->name = line.substr(1, std::string::npos);
      } else {
	return false;
      }
      getline(ss, line);
      if (!line.substr(0, 6).compare("route=")) {
	savedRS->route = line.substr(6, std::string::npos);
      } else {
	return false;
      }
      getline(ss, line);
      if (!line.substr(0, 5).compare("stop=")) {
	savedRS->stop = line.substr(5, std::string::npos);
      } else {
	return false;
      }
      savedRouteStops.push_back(savedRS);
    }
  }
  return true;
}

bool ConfigFile::lastUsageExpired() {
  // TODO
  return true;
}

bool ConfigFile::lastRouteDownloadExpired() {
  // TODO
  return true;
}
