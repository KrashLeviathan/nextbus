#ifndef PREDICTIONS_PARSER_H
# define PREDICTIONS_PARSER_H

# include <string>
# include <vector>
# include <map>
# include "xml_parser.h"
# include "route.h"

# define ATTR_ROUTE_TAG        'a'
# define ATTR_ROUTE_TITLE      'b'
# define ATTR_STOP_TITLE       'c'
# define ATTR_MESSAGE          'd'
# define ATTR_DIRECTION_TAG    'e'
# define ATTR_DIRECTION_TITLE  'f'
# define ATTR_MINUTES          'g'
# define ATTR_EPOCH_TIME       'h'
# define ATTR_IS_DEPARTURE     'i'
# define ATTR_DIR_NO_PREDICTS  'j'

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
  void parse_element_open();
  std::map<char, std::string> *parse_attributes();
  void parse_direction();
  void parse_predictions();
  void parse_prediction();
  void parse_message();
 public:
  std::vector<Predictions *> predictions;
  PredictionsParser(std::string &s) : XmlParser(s) {
    tempPredictions = NULL;
    tempPrediction = NULL;
  }
  void parse();
  std::string results();
};

#endif
