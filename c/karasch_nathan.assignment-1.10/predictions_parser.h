#ifndef PREDICTIONS_PARSER_H
# define PREDICTIONS_PARSER_H

# include <string>
# include <vector>
# include <map>
# include "xml_parser.h"
# include "route.h"

# define ATTR_ROUTE_TAG        'a'
# define ATTR_ROUTE_TITLE      'b'
# define ATTR_STOP_TAG         'c'
# define ATTR_STOP_TITLE       'd'
# define ATTR_MESSAGE          'e'
# define ATTR_DIRECTION_TAG    'f'
# define ATTR_DIRECTION_TITLE  'g'
# define ATTR_MINUTES          'h'
# define ATTR_EPOCH_TIME       'i'
# define ATTR_IS_DEPARTURE     'j'
# define ATTR_DIR_NO_PREDICTS  'k'

class Prediction {
 public:
  std::string strMinutes;
  std::string strEpochTime;
  std::string strIsDeparture;
  std::string directionTag;
  std::string directionTitle;
  int minutes;
  int epochTime;
  bool isDeparture;
  void applyStringValues();
};

class Predictions {
 public:
  std::string routeTag;
  std::string routeTitle;
  std::string stopTag;
  std::string stopTitle;
  std::vector<Prediction *> predictions;
  std::string messageText;
  std::string dirTitleBecauseNoPredictions;
};

class PredictionsParser : public XmlParser {
 private:
  Predictions *tempPredictions;
  Prediction *tempPrediction;
  std::string tempDirection;
  void parse_direction();
  void parse_predictions();
  void parse_prediction();
  void parse_message();
  void element_open_actions();
  void element_close_actions();
  char key_from_string(std::string *str);
 public:
  std::vector<Predictions *> predictions;
  PredictionsParser(std::string &s) : XmlParser(s) {
    tempPredictions = NULL;
    tempPrediction = NULL;
  }
  std::string results();
};

#endif
