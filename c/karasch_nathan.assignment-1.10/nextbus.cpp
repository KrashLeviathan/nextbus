#include <iostream>
#include "io.h"
#include "config.h"
#include "connection.h"


int main(int argc, char *argv[]) {
  std::string filepath;
  std::string xml_string;
  // CommandLineAction *clAction;
  ConfigFile *configFile;

  // Test the command line argument parser
  // clAction = parse_arguments(argc, argv);

  // Test config file creation
  filepath = get_filepath("config.nextbus");
  configFile = new ConfigFile(filepath);
  

  // Test file curling
  // agency = DEFAULT_AGENCY;
  // xml_string = routeList();

  // std::cout << xml_string << std::endl;

  // delete clAction;
  delete configFile;
  
  return 0;
}
