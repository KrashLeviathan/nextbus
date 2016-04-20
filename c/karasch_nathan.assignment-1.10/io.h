#ifndef IO_H
# define IO_H

#include <vector>
#include <string>
#include <stdint.h>

# define NB_SUBPATH     ".nextbus"

# define IO_NORMAL       "\x1B[0m"
# define IO_RED         "\x1B[31m"
# define IO_GREEN       "\x1B[32m"
# define IO_YELLOW      "\x1B[33m"
# define IO_BLUE        "\x1B[34m"
# define IO_MAGENTA     "\x1B[35m"
# define IO_CYAN        "\x1B[36m"
# define IO_WHITE       "\x1B[37m"

# define ACTION_AGENCY_LIST   0x00000001  // -a --agencies
# define ACTION_AGENCY_STORE  0x00000002  // -A --AgencyStore
# define ACTION_ROUTE_LIST    0x00000004  // -r --routes
# define ACTION_ROUTE_STORE   0x00000008  // -R --RouteStore
# define ACTION_SCHEDULE_LIST 0x00000010  // -s --schedule
# define ACTION_HELP          0x00000020  // -h --help
# define ACTION_PREDICT_STOP  0x00000040  // -p --predictstop
# define ACTION_PREDICT_ROUTE 0x00000080  // -P --PredictRoute
# define ACTION_SAVE_CUSTOM   0x00000100  // -S --Save
# define ACTION_ONLINE        0x00000200  // -o --online
# define ACTION_CACHED        0x00000400  // -c --cached
# define ACTION_USE_SAVED     0x00000800  // <save_name>
# define ACTION_BIT12         0x00001000
# define ACTION_BIT13         0x00002000
# define ACTION_BIT14         0x00004000
# define ACTION_BIT15         0x00008000
# define ACTION_BIT16         0x00010000
# define ACTION_BIT17         0x00020000
# define ACTION_BIT18         0x00040000
# define ACTION_BIT19         0x00080000
# define ACTION_BIT20         0x00100000
# define ACTION_BIT21         0x00200000
# define ACTION_BIT22         0x00400000
# define ACTION_BIT23         0x00800000
# define ACTION_BIT24         0x01000000
# define ACTION_BIT25         0x02000000
# define ACTION_BIT26         0x04000000
# define ACTION_BIT27         0x08000000
# define ACTION_BIT28         0x10000000
# define ACTION_BIT29         0x20000000
# define ACTION_BIT30         0x40000000
# define ACTION_BIT31         0x80000000

typedef uint32_t Action;

class CommandLineAction {
 public:
  std::string agency;
  std::string route;
  std::string stop;
  std::string save;
  std::vector<std::string *> saveUses;
  Action actions;
  std::string to_string();
};

void usage();
void error(const char *message);
std::string get_file_contents(std::string &filepath);
bool set_file_contents(std::string &filepath, std::string &contents);
std::string get_filepath(const char *filename);
CommandLineAction *parse_arguments(int argc, char *argv[]);

#endif
