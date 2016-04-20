#ifndef CONFIG_H
# define CONFIG_H

# include <fstream>
# include <string>
# include <vector>
# include <ctime>

# define VERSION_NUMBER        "1"
# define DEFAULT_AGENCY        "cyride"
# define CONFIG_HEADER         "NextBus Configuration File"
# define SEC_PER_DAY           86400
# define DAYS_TO_EXPIRE        1

class SavedRouteStop {
 public:
  std::string name;
  std::string route;
  std::string stop;
  SavedRouteStop(std::string n, std::string r, std::string s) {
    name = n;
    route = r;
    stop = s;
  }
  SavedRouteStop() {}
};

class ConfigFile {
 public:
  time_t lastChange; // TODO: refactor as lastUsage and implement
  time_t lastRouteDownload; // TODO: implement
  std::string agency;
  std::vector<SavedRouteStop *> savedRouteStops;

  ConfigFile(std::string &filepath);
  bool update();
  bool lastChangeExpired();
  bool lastRouteDownloadExpired();

 private:
  std::string filepath;
  std::string contents;
  bool parse();
  void print_details();
};

#endif
