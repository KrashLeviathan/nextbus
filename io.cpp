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
    << "                 [ <save-name-1> <save-name-2> ...           ]"
    << std::endl
    << "                 [ -a | --agencies                           ]"
    << std::endl
    << "                 [ -A | --AgencyStore  <agency>              ]"
    << std::endl
    << "                 [ -c | --cached                             ]"
    << std::endl
    << "                 [ -h | --help                               ]"
    << std::endl
    << "                 [ -m | --minutes      <save-name>           ]"
    << std::endl
    << "                 [ -o | --online                             ]"
    << std::endl
    << "                 [ -p | --predictstop  <stop>                ]"
    << std::endl
    << "                 [ -P | --PredictRoute <route> <stop>        ]"
    << std::endl
    << "                 [ -r | --routes                             ]"
    << std::endl
    << "                 [ -S | --Save         <name> <route> <stop> ]"
    << std::endl
    << "                 [ -s | --schedule     <route>               ]"
    << std::endl
    << "                 [ -l | --liststops    <route>               ]"
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

bool set_file_contents(std::string &filepath, std::string &contents) {
  std::ofstream file;
  
  file.open(filepath.c_str());
  if (file.is_open()) {
    file << contents << std::endl;
    file.close();
    return true;
  }
  return false;
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
  CommandLineAction *cla = new CommandLineAction();

  cla->actions = 0;
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
	  cla->actions = cla->actions | ACTION_AGENCY_STORE;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument: agency
	    cla->agency = argv[++i];
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
	  cla->actions = cla->actions | ACTION_PREDICT_STOP;
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
	  cla->actions = cla->actions | ACTION_PREDICT_ROUTE;
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
          cla->actions = cla->actions | ACTION_AGENCY_LIST;
          break;
        case 'r':
	  // List all routes
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-routes"))) {
            usage();
          }
	  cla->actions = cla->actions | ACTION_ROUTE_LIST;
          break;
        case 'l':
      // List stops
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-liststops"))) {
            usage();
          }
      cla->actions = cla->actions | ACTION_LIST_STOPS;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument: route
        cla->route = argv[++i];
          } else {
        usage();
      }
      break;
        case 's':
	  // List bus schedule
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-schedule"))) {
            usage();
          }
	  cla->actions = cla->actions | ACTION_SCHEDULE_LIST;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument: route
	    cla->route = argv[++i];
          } else {
	    usage();
	  }
          break;
	case 'S':
	  // Save a custom variable with route & stop info
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-Save"))) {
            usage();
          }
	  cla->actions = cla->actions | ACTION_SAVE_CUSTOM;
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
	case 'o':
	  // Force use online data
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-online"))) {
            usage();
          }
	  cla->actions = cla->actions | ACTION_ONLINE;
          goto param_not_complete;
	case 'c':
	  // Force use cached data
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-cached"))) {
            usage();
          }
	  cla->actions = cla->actions | ACTION_CACHED;
          goto param_not_complete;
	case 'h':
	  // Show help information
	  cla->actions = cla->actions | ACTION_HELP;
	  break;
	case 'm':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-minutes"))) {
            usage();
          }
	  cla->actions = cla->actions | ACTION_MINUTES;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            // Argument: save_name
	    cla->saveUses.push_back(new std::string(argv[++i]));
          } else {
	    usage();
	  }
          break;
        default:
          usage();
        }
	param_complete = true;
      } else { /* No dash */
	// Take custom variables that were stored in the
	// config file and fetch route information with them
	cla->actions = cla->actions | ACTION_USE_SAVED;
	cla->saveUses.push_back(new std::string(argv[i]));
      }
    param_not_complete:
      // Allows you to jump over the `param_complete = true` line
      // if there is an action that can be combined with other actions
      std::cout << "";
    }
  } else {
    usage();
  }
  return cla;
}

std::string CommandLineAction::to_string() {
  std::stringstream ss;
  int i;
  ss << "Agency:  " << agency << std::endl
     << "Route:   " << route << std::endl
     << "Stop:    " << stop << std::endl
     << "Save:    " << save << std::endl
     << "Actions: " << actions << std::endl 
     << "Save Uses:" << std::endl;
  for (i = 0; i < saveUses.size(); i++) {
    ss << "   " << *saveUses[i] << std::endl;
  }
  return ss.str();
}
