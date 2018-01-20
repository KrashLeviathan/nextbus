#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>
#include "stop_list_parser.h"
#include "io.h"

char StopListParser::key_from_string(std::string *str) {
    if (!str->compare("tag")) {
        return ATTR_STOP_TAG;
    } else if (!str->compare("title")) {
        return ATTR_STOP_TITLE;
    } else if (!str->compare("shouldRetry")) {
        // Must have this one
        return ATTR_ERROR_SHOULD_RETRY;
    } else {
        return 'Z';
    }
}

std::string StopListParser::results() {
    std::stringstream ss;
    int i;

    if (stops.empty()) {
        error("StopListParser::results()");
    }

    ss << IO_GREEN "STOP TITLE                     "
       << "(STOP TAG)" IO_NORMAL
       << std::endl << std::endl;
    for (i = 0; i < stops.size(); i++) {
        if (stops[i]->title.size() == 0) {
            continue;
        }
        ss << std::left << std::setw(30) << stops[i]->title
           << std::setw(0) << " (" IO_YELLOW << stops[i]->tag
           << IO_NORMAL ")" << std::endl;
    }
    ss << std::endl
       << IO_GREEN "NOTE: When you get predictions or "
       << "set route/stop variables,"
       << std::endl << "make sure to use the " IO_YELLOW
       << "STOP TAG" IO_GREEN "." IO_NORMAL;
    return ss.str();
}

void StopListParser::parse_stop() {
    std::map<char, std::string> *attributeMap;

    tempStopListing = new StopListing();

    attributeMap = parse_attributes();
    tempStopListing->tag = (*attributeMap)[ATTR_STOP_TAG];
    tempStopListing->title = (*attributeMap)[ATTR_STOP_TITLE];
    stops.push_back(tempStopListing);
}

void StopListParser::element_open_actions() {
    if (!substring.compare("stop")) {
        parse_stop();
    }
}

void StopListParser::element_close_actions() {
    // No actions necessary because <stop/> is self-closing
}
