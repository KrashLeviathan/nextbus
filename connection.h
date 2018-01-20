#ifndef CONNECTION_H
# define CONNECTION_H

# include <string>
# include <vector>

std::string agencyList();
std::string routeList(const char *agency);
std::string routeConfig(const char *agency, const char *optionalRouteTag);
std::string stopList(const char *agency, const char *routeTag);
std::string predictions(const char *agency, const char *stopTag);
std::string predictions(const char *agency, const char *stopTag,
			const char *routeTag);
std::string predictionsForMultiStops(const char *agency,
		     std::vector<std::string> stopTagVector);
std::string schedule(const char *agency, const char *routeTag);
std::string nb_messages(const char *agency, std::vector<std::string *> routeTagVector);

#endif
