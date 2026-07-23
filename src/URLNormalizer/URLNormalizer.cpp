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
        // Keep as is
    }

    // Root-relative URL
    else if (!result.empty() && result[0] == '/')
    {
        // Find the first '/' after "http://" or "https://"
        size_t start = baseURL.find("//");

        if (start != std::string::npos)
        {
            start += 2; // Move past "//"

            size_t pos = baseURL.find('/', start);

            if (pos != std::string::npos)
                result = baseURL.substr(0, pos) + result;
            else
                result = baseURL + result;
        }
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

    // Remove fragment (#section)
    size_t hash = result.find('#');

    if (hash != std::string::npos)
        result = result.substr(0, hash);

    // Remove trailing slash
    if (result.length() > 1 && result.back() == '/')
        result.pop_back();

    return result;
}

std::string URLNormalizer::getDomain(const std::string& url)
{
    size_t start = url.find("//");

    if (start == std::string::npos)
        return "";

    start += 2;

    size_t end = url.find('/', start);

    if (end == std::string::npos)
        return url;

    return url.substr(0, end);
}