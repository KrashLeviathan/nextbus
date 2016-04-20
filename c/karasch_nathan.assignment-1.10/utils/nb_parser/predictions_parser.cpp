#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "predictions_parser.h"
#include "route.h"
#include "io.h"

char PredictionsParser::key_from_string(std::string *str) {
  if (!str->compare("routeTag")) {
    return ATTR_ROUTE_TAG;
  } else if (!str->compare("routeTitle")) {
    return ATTR_ROUTE_TITLE;
  } else if (!str->compare("stopTitle")) {
    return ATTR_STOP_TITLE;
  } else if (!str->compare("text")) {
    return ATTR_MESSAGE;
  } else if (!str->compare("minutes")) {
    return ATTR_MINUTES;
  } else if (!str->compare("epochTime")) {
    return ATTR_EPOCH_TIME;
  } else if (!str->compare("isDeparture")) {
    return ATTR_IS_DEPARTURE;
  } else if (!str->compare("dirTag")) {
    return ATTR_DIRECTION_TAG;
  } else if (!str->compare("title")) {
    return ATTR_DIRECTION_TITLE;
  } else if (!str->compare("dirTitleBecauseNoPredictions")) {
    return ATTR_DIR_NO_PREDICTS;
  } else {
    return 'Z';
  }
}

std::string PredictionsParser::results() {
  std::stringstream ss;
  int i, j;
  std::string direction;
  
  if (predictions.empty()) {
    error("PredictionsParser::results()");
  }
  
  if (predictions[0]->dirTitleBecauseNoPredictions.empty()) {
    // Successful predictions results
    for (i = 0; i < predictions.size(); i++) {
      ss << "NEXTBUS PREDICTIONS:" << std::endl << std::endl
	 << "   Route:   " IO_YELLOW << predictions[i]->routeTitle
	 << " (" << predictions[i]->routeTag << ")" IO_NORMAL << std::endl
	 << "   Stop:    " << predictions[i]->stopTitle << std::endl;
      for (j = 0; j < predictions[i]->predictions.size(); j++) {
	if (direction.compare(predictions[i]
			      ->predictions[j]->directionTitle)) {
	  direction = predictions[i]->predictions[j]->directionTitle;
	  ss << std::endl << "      Direction:  " << direction
	     << std::endl;
	}
	ss << "                  Minutes until "
	   << ((predictions[i]->predictions[j]->isDeparture) ?
	       "departure:  " : "arrival:    ")
	   << predictions[i]->predictions[j]->strMinutes << std::endl;
      }
      ss << std::endl
	 << "   Messages:" << std::endl
	 << predictions[i]->messageText << std::endl;
    }
  } else {
    // No predictions
    ss << IO_RED "There are no predictions at this time for:" IO_NORMAL
       << std::endl << "   Route:      "
       << predictions[0]->routeTitle
       << " (" << predictions[0]->routeTag << ")" << std::endl
       << "   Stop:       "
       << predictions[0]->stopTitle << std::endl
       << "   Direction:  "
       << predictions[0]->dirTitleBecauseNoPredictions;
  }
  return ss.str();
}

void Prediction::applyStringValues() {
  std::stringstream ss1 (strMinutes);
  std::stringstream ss2 (strEpochTime);
  ss1 >> minutes;
  ss2 >> epochTime;
  isDeparture = (!strIsDeparture.compare("true"));
}

void PredictionsParser::parse_message() {
  std::map<char, std::string> *attributeMap;

  attributeMap = parse_attributes();
  tempPredictions->messageText = (*attributeMap)[ATTR_MESSAGE];
}

void PredictionsParser::parse_direction() {
  std::map<char, std::string> *attributeMap;

  attributeMap = parse_attributes();
  tempDirection = (*attributeMap)[ATTR_DIRECTION_TITLE];
}

void PredictionsParser::parse_prediction() {
  std::map<char, std::string> *attributeMap;

  tempPrediction = new Prediction();

  attributeMap = parse_attributes();

  tempPrediction->directionTag = (*attributeMap)[ATTR_DIRECTION_TAG];
  tempPrediction->directionTitle = tempDirection;
  tempPrediction->strMinutes = (*attributeMap)[ATTR_MINUTES];
  tempPrediction->strEpochTime = (*attributeMap)[ATTR_EPOCH_TIME];
  tempPrediction->strIsDeparture = (*attributeMap)[ATTR_IS_DEPARTURE];

  tempPrediction->applyStringValues();
  
  tempPredictions->predictions.push_back(tempPrediction);
}

void PredictionsParser::parse_predictions() {
  std::map<char, std::string> *attributeMap;

  tempPredictions = new Predictions();

  attributeMap = parse_attributes();
  tempPredictions->routeTag = (*attributeMap)[ATTR_ROUTE_TAG];
  tempPredictions->routeTitle = (*attributeMap)[ATTR_ROUTE_TITLE];
  tempPredictions->stopTitle = (*attributeMap)[ATTR_STOP_TITLE];
  tempPredictions->dirTitleBecauseNoPredictions = (*attributeMap)[ATTR_DIR_NO_PREDICTS];
}

void PredictionsParser::element_open_actions() {
  if (!substring.compare("predictions")) {
    parse_predictions();
  } else if (!substring.compare("prediction")) {
    parse_prediction();
  } else if (!substring.compare("direction")) {
    parse_direction();
  } else if (!substring.compare("message")) {
    parse_message();
  }
}

void PredictionsParser::element_close_actions() {
  if (!substring.compare("predictions")) {
    // Predictions complete
    predictions.push_back(tempPredictions);
  }
}
