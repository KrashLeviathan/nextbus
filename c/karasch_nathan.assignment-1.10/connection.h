#ifndef CONNECTION_H
# define CONNECTION_H

# include <string>
# include <vector>

std::string agencyList();
std::string routeList();
std::string routeConfig(const char *routeTag);
std::string predictions(const char *stopTag);
std::string predictions(const char *stopTag, const char *routeTag);
std::string predictionsForMultiStops(std::vector<std::string> stopTagVector);
std::string schedule(const char *routeTag);
std::string messages(std::vector<std::string> routeTagVector);

#endif
