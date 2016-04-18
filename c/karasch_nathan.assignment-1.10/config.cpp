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
  std::cout << "Last Change" << std::endl;
  std::cout << lastChange << std::endl;
  std::cout << "Last Route DL" << std::endl;
  std::cout << lastRouteDownload << std::endl;
  std::cout << "Agency" << std::endl;
  std::cout << agency << std::endl;
  std::cout << "Routes" << std::endl;
  for (i = 0; i < routes.size(); i++) {
    std::cout << *routes[i] << std::endl;
  }
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
      << "   or corrupted. Use the command line arguments to add new routes,"
      << std::endl
      << "   stops, etc safely. If you want to edit the config file manually,"
      << std::endl
      << "   do so with caution!"
      << std::endl << std::endl
      << "Creating a new config file at "
      << filepath << std::endl << std::endl;
    lastChange = 0;
    lastRouteDownload = 0;
    agency = DEFAULT_AGENCY;
    update();
  }
  print_details();
  
  // add_config_stop(file, "home",   "2E", "1123");
  // add_config_stop(file, "school", "2W", "1077");
}

bool ConfigFile::update() {
  std::ofstream file;
  int i;
  
  file.open(filepath.c_str());
  if (file.is_open()) {
    file << "NextBus Configuration File" << std::endl;
    file << "version " << VERSION_NUMBER << std::endl << std::endl;
    
    file << ":LAST CHANGE" << std::endl;
    file << lastChange << std::endl << std::endl;
    
    file << ":LAST ROUTE DOWNLOAD" << std::endl;
    file << lastRouteDownload << std::endl << std::endl;
    
    file << ":AGENCY" << std::endl;
    file << agency << std::endl << std::endl;

    file << ":ROUTES" << std::endl;
    if (!routes.empty()) {
      for (i = 0; i < routes.size(); i++) {
	file << *routes[i] << std::endl;
      }
    }
    file << std::endl;

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

  CHECK_HEADING("NextBus Configuration File");
  CHECK_HEADING("version " VERSION_NUMBER);
  getline(ss, line);
  CHECK_HEADING(":LAST CHANGE");
  getline(ss, line);
  stringToInt = new std::stringstream(line);
  *stringToInt >> lastChange;
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
  CHECK_HEADING(":ROUTES");
  while (getline(ss, line) && line.compare(":SAVED")) {
    if (line.compare("")) {
      // If the line is not empty, save the route
      routes.push_back(new std::string(line));
    }
  }
  if (!line.compare(":SAVED")) {
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
  } else {
    std::cout << "ERROR parse(): " << line << std::endl;
    return false;
  }
  return true;
}
