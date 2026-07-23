#ifndef URLNORMALIZER_H
#define URLNORMALIZER_H

#include <string>

class URLNormalizer
{
public:
    URLNormalizer();

    std::string normalize(const std::string& baseURL,
                          const std::string& url);

    std::string getDomain(const std::string& url);
};

#endif