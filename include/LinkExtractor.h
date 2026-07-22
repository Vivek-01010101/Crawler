#ifndef LINKEXTRACTOR_H
#define LINKEXTRACTOR_H

#include <string>
#include "Frontier.h"

class LinkExtractor
{
public:
    LinkExtractor();

    void extractLinks(const std::string& html,
                      const std::string& baseURL,
                      Frontier& frontier,
                      int currentDepth);
};

#endif