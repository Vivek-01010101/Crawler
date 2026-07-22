#include "../../include/URLNormalizer.h"

URLNormalizer::URLNormalizer()
{
}

std::string URLNormalizer::normalize(const std::string& baseURL,
                                     const std::string& url)
{
    std::string result = url;

    // Absolute URL
    if (result.find("http://") == 0 ||
        result.find("https://") == 0)
    {
        // keep as is
    }

    // Root-relative
    else if (!result.empty() && result[0] == '/')
    {
        size_t pos = baseURL.find('/', 8);

        if (pos != std::string::npos)
            result = baseURL.substr(0, pos) + result;
        else
            result = baseURL + result;
    }

    // Relative URL
    else
    {
        size_t pos = baseURL.rfind('/');

        if (pos != std::string::npos)
            result = baseURL.substr(0, pos + 1) + result;
        else
            result = baseURL + "/" + result;
    }

    // Remove fragment
    size_t hash = result.find('#');

    if (hash != std::string::npos)
        result = result.substr(0, hash);

    // Remove trailing slash
    if (result.length() > 1 && result.back() == '/')
        result.pop_back();

    return result;
}