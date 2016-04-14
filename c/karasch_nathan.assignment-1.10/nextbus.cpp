#include <iostream>
#include "io.h"
#include "config.h"

int main(int argc, char *argv[]) {
  std::string filepath;

  // Test config file creation
  filepath = get_filepath("config.nextbus");
  init_config(filepath);
  
  return 0;
}
