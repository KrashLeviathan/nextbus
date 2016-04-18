#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <sys/stat.h>

#include "io.h"

struct stat sb;

void usage() {
  std::cout
    << "Usage: nextbus [" << std::endl
    << "                 [ -a | --agencies     ]                |"
    << std::endl
    << "                 [ -A | --AgencyStore  ] <agency>       |"
    << std::endl
    << "                 [ -r | --routes       ]                |"
    << std::endl
    << "                 [ -R | --RouteStore   ] <route>        |"
    << std::endl
    << "                 [ -s | --schedules    ]                |"
    << std::endl
    << "                 [ -m | --messages     ]                |"
    << std::endl
    << "                 [ -p | --predictstop  ] <stop>         |"
    << std::endl
    << "                 [ -P | --PredictRoute ] <route> <stop> |"
    << std::endl
    << "                 [ -S | --Save         ] <name> <route> <stop>"
    << std::endl
    << "               ]" << std::endl;
  exit(1);
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

/**
 * The parse_arguments function was largely Jeremy Sheaffer's
 * handiwork from the ComS327 rogue-like game project. I modified
 * it to handle command line switches for the nextbus project.
 */
CommandLineAction *parse_arguments(int argc, char **argv) {
  uint32_t i;
  uint32_t long_arg;
  bool param_complete;
  Action actions;
  CommandLineAction *cla = new CommandLineAction();
  
  actions = 0;
  param_complete = false;

 if (argc > 1) {
    for (i = 1, long_arg = 0; i < argc; i++, long_arg = 0) {
      if (param_complete) {
	// A switch and its arguments were already found, yet
	// there was extra stuff in the argument list.
	usage();
      }
      if (argv[i][0] == '-') { /* All switches start with a dash */
        if (argv[i][1] == '-') {
          argv[i]++;    /* Make the argument have a single dash so we can */
          long_arg = 1; /* handle long and short args at the same place.  */
        }
        switch (argv[i][1]) {
        case 'A':
	  // Stores the agency used to load bus information
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-AgencyStore"))) {
            usage();
          }
	  actions = actions | ACTION_AGENCY_STORE;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument: agency
	    cla->agency = argv[++i];
          } else {
	    usage();
	  }
          break;
        case 'R':
	  // Store a route in the configuration for quick access
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-RouteStore"))) {
            usage();
          }
	  actions = actions | ACTION_ROUTE_STORE;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument: route
	    cla->route = argv[++i];
          } else {
	    usage();
	  }
          break;
        case 'p':
	  // Predict the arrival times for busses at a given stop
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-predictstop"))) {
            usage();
          }
	  actions = actions | ACTION_PREDICT_STOP;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument: stop
	    cla->stop = argv[++i];
          } else {
	    usage();
	  }
          break;
        case 'P':
	  // Predict the arrival time for a given route & stop
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-PredictRoute"))) {
            usage();
          }
	  actions = actions | ACTION_PREDICT_ROUTE;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument 1: route
	    cla->route = argv[++i];
          } else {
	    usage();
	  }
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument 2: stop
	    cla->stop = argv[++i];
          } else {
	    usage();
	  }
          break;
        case 'a':
	  // List all agencies
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-agencies"))) {
            usage();
          }
          actions = actions | ACTION_AGENCY_LIST;
          break;
        case 'r':
	  // List all routes
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-routes"))) {
            usage();
          }
	  actions = actions | ACTION_ROUTE_LIST;
          break;
        case 's':
	  // List bus schedules
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-schedules"))) {
            usage();
          }
	  actions = actions | ACTION_SCHEDULE_LIST;
          break;
        case 'm':
	  // List bus messages
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-messages"))) {
            usage();
          }
	  actions = actions | ACTION_MESSAGE_LIST;
          break;
	case 'S':
	  // Save a custom variable with route & stop info
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-Save"))) {
            usage();
          }
	  actions = actions | ACTION_SAVE_CUSTOM;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument 1: save name
	    cla->save = argv[++i];
          } else {
	    usage();
	  }
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument 2: route
	    cla->route = argv[++i];
          } else {
	    usage();
	  }
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument 3: stop
	    cla->stop = argv[++i];
          } else {
	    usage();
	  }
          break;
        default:
          usage();
        }
	param_complete = true;
      } else { /* No dash */
	// TODO: Take custom variables that were stored in the
	// config file and fetch route information with them
        usage();
      }
    }
  }
 return cla;
}
