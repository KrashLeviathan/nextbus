#ifndef ROUTE_H
# define ROUTE_H

#include <string>
#include <vector>

using namespace std;

class Stop {
 public:
  string tag;
  string title;
  string to_string();
};

class Direction {
 public:
  string tag;
  string title;
  vector<Stop *> stops;
  string to_string();
};

class Route {
 public:
  string tag;
  string title;
  string color;
  string oppositeColor;
  vector<Stop> stops;
  vector<Direction> directions;
  Stop *find_stop(string &tag);
  string to_string();
};

#endif
