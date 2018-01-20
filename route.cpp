#include "route.h"

Stop *Route::find_stop(std::string &tag) {
  std::vector<Stop>::iterator it;
  Stop *s;

  for (it = stops.begin(); it != stops.end(); it++) {
    s = &(*it);
    if (!tag.compare(s->tag)) {
      return s;
    }
  }
  return NULL;
}

std::string Stop::to_string() {
  std::string str("        Stop: ");

  str += tag;
  str += ", ";
  str += title;
  str += "\n";
  return str;
}

std::string Direction::to_string() {
  std::vector<Stop *>::iterator stopIt;
  std::string str("    Direction: ");

  str += tag;
  str += ", ";
  str += title;
  str += "\n      Stops:\n";
  for (stopIt = stops.begin(); stopIt != stops.end(); stopIt++) {
    str += (*stopIt)->to_string();
  }
  return str;
}

std::string Route::to_string() {
  std::vector<Stop>::iterator stopIt;
  std::vector<Direction>::iterator dirIt;
  std::string str("Route: ");

  str += tag;
  str += ", ";
  str += title;
  str += ", ";
  str += color;
  str += ", ";
  str += oppositeColor;
  str += "\n  Stops:\n";
  for (stopIt = stops.begin(); stopIt != stops.end(); stopIt++) {
    str += (*stopIt).to_string();
  }
  str += "\n  Directions:\n";
  for (dirIt = directions.begin(); dirIt != directions.end(); dirIt++) {
    str += (*dirIt).to_string();
  }
  return str;
}
