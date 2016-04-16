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

// std::vector<std::string *> *parse_switch(int argc, char *argv[],
// 		   uint32_t *i, uint32_t *long_arg,
// 		   const char *long_switch, int switch_args,
//                    Action switch_action, Action *actions) {
//   int j;
//   std::vector<std::string *> *switch_arguments = new std::vector<std::string *>();

//   if ((!(*long_arg) && argv[*i][2]) ||
//       (*long_arg && strcmp(argv[*i], long_switch))) {
//     usage();
//   }
//   *actions = *actions | switch_action;
//   for (j = 0; j < switch_args; j++) {
//     if ((argc > *i + 1) && argv[*i + 1][0] != '-') {
//       // Argument j
//       switch_arguments->push_back(new std::string(argv[++(*i)]));
//     } else {
//       usage();
//     }
//   }
//   return switch_arguments;
// }

// /**
//  * The parse_arguments function was largely Jeremy Sheaffer's
//  * handiwork from the ComS327 rogue-like game project. I modified
//  * it to handle command line switches for the nextbus project.
//  */
// void parse_arguments(int argc, char *argv[], Action *actions) {
//   uint32_t i;
//   uint32_t long_arg;
//   bool param_complete;
//   std::vector<std::string *> *argument_vector;
//   std::string *agency_param;
//   std::string *route_param;
//   std::string *stop_param;
//   std::string *save_param;
  
//   actions = 0;
//   param_complete = false;
//   agency_param = NULL;
//   route_param = NULL;
//   stop_param = NULL;
//   save_param = NULL;

//  if (argc > 1) {
//     for (i = 1, long_arg = 0; i < argc; i++, long_arg = 0) {
//       if (param_complete) {
// 	// A switch and its arguments were already found, yet
// 	// there was extra stuff in the argument list.
// 	usage();
//       }
//       if (argv[i][0] == '-') { /* All switches start with a dash */
//         if (argv[i][1] == '-') {
//           argv[i]++;    /* Make the argument have a single dash so we can */
//           long_arg = 1; /* handle long and short args at the same place.  */
//         }
//         switch (argv[i][1]) {
//         case 'A':
// 	  // Stores the agency used to load bus information
// 	  argument_vector = parse_switch(argc, argv, &i, &long_arg,
// 					 "-AgencyStore", 1,
// 					 ACTION_AGENCY_STORE, actions);
// 	  agency_param = (*argument_vector)[0];
//           break;
//         case 'R':
// 	  // Store a route in the configuration for quick access
// 	  argument_vector = parse_switch(argc, argv, &i, &long_arg,
// 					 "-RouteStore", 1,
// 					 ACTION_ROUTE_STORE, actions);
// 	  route_param = (*argument_vector)[0];
//           break;
//         case 'p':
// 	  // Predict the arrival times for busses at a given stop
// 	  argument_vector = parse_switch(argc, argv, &i, &long_arg,
// 					 "-predictstop", 1,
// 					 ACTION_PREDICT_STOP, actions);
// 	  stop_param = (*argument_vector)[0];
//           break;
//         case 'P':
// 	  // Predict the arrival time for a given route & stop
// 	  argument_vector = parse_switch(argc, argv, &i, &long_arg,
// 					 "-PredictRoute", 2,
// 					 ACTION_PREDICT_ROUTE, actions);
// 	  route_param = (*argument_vector)[0];
// 	  stop_param = (*argument_vector)[1];
//           break;
//         case 'a':
// 	  // List all agencies
// 	  parse_switch(argc, argv, &i, &long_arg,
// 		       "-agencies", 0, ACTION_AGENCY_LIST, actions);
//           break;
//         case 'r':
// 	  // List all routes
// 	  parse_switch(argc, argv, &i, &long_arg,
// 		       "-routes", 0, ACTION_ROUTE_LIST, actions);
//           break;
//         case 's':
// 	  // List bus schedules
// 	  parse_switch(argc, argv, &i, &long_arg,
// 		       "-schedules", 0, ACTION_SCHEDULE_LIST, actions);
//           break;
//         case 'm':
// 	  // List bus messages
// 	  parse_switch(argc, argv, &i, &long_arg,
// 		       "-messages", 0, ACTION_MESSAGE_LIST, actions);
//           break;
// 	case 'S':
// 	  // Save a custom variable with route & stop info
// 	  argument_vector = parse_switch(argc, argv, &i, &long_arg,
// 					 "-Save", 3,
// 					 ACTION_SAVE_CUSTOM, actions);
// 	  save_param = (*argument_vector)[0];
// 	  route_param = (*argument_vector)[1];
// 	  stop_param = (*argument_vector)[2];
//           break;
//         default:
//           usage();
//         }
// 	param_complete = true;
//       } else { /* No dash */
// 	// TODO: Take custom variables that were stored in the
// 	// config file and fetch route information with them
//         usage();
//       }
//     }
//   }
//  std::cout << "DONE" << std::endl;
//  std::cout << agency_param << std::endl;
//  std::cout << route_param << std::endl;
//  std::cout << stop_param << std::endl;
//  std::cout << save_param << std::endl;
// }

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
 std::cout << "DONE" << std::endl;
 std::cout << "            Action: " << actions << std::endl;
 std::cout << "Agency: " << cla->agency << std::endl;
 std::cout << "Route:  " << cla->route << std::endl;
 std::cout << "Stop:   " << cla->stop << std::endl;
 std::cout << "Save:   " << cla->save << std::endl;
 return cla;
}
