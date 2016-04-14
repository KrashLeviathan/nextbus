#include "xml_parser.h"

void *XmlParser::next(const char *type) {
  return static_cast<void *>(&text);
}
