#include <iostream>
#include "io.h"
#include "config.h"
#include "connection.h"


int main(int argc, char *argv[]) {
  std::string filepath;
  std::string xml_string;
  CommandLineAction *clAction;
  ConfigFile *configFile;

  // Parse command line arguments
  clAction = parse_arguments(argc, argv);

  // Load settings from the config file
  filepath = get_filepath("config.nextbus");
  configFile = new ConfigFile(filepath);
  

  // Test file curling
  // agency = DEFAULT_AGENCY;
  // xml_string = routeList();

  // std::cout << xml_string << std::endl;

  // Cleanup
  delete clAction;
  delete configFile;
  
  return 0;
}
