#include "../../include/URLNormalizer.h"

URLNormalizer::URLNormalizer()
{
}

std::string URLNormalizer::normalize(const std::string& baseURL,
                                     const std::string& url)
{
    // Ignore empty
    if (url.empty())
        return "";

    // Ignore anchors
    if (url[0] == '#')
        return url;

    // Ignore mailto
    if (url.find("mailto:") == 0)
        return url;

    // Ignore javascript
    if (url.find("javascript:") == 0)
        return url;

    // Ignore tel
    if (url.find("tel:") == 0)
        return url;

    // Absolute URL
    if (url.find("http://") == 0 ||
        url.find("https://") == 0)
    {
        std::string result = url;

        // Remove fragment
        size_t hash = result.find('#');
        if (hash != std::string::npos)
            result = result.substr(0, hash);

        // Remove trailing slash
        if (result.length() > 1 && result.back() == '/')
            result.pop_back();

        return result;
    }

    // Extract domain
    std::string domain = getDomain(baseURL);

    std::string result;

    // Root-relative URL
    if (url[0] == '/')
    {
        result = domain + url;
    }
    // else
    // {
    //     // Relative URL
    //     result = domain + "/" + url;
    // }
    else
    {
        std::string resultBase = baseURL;

        // Remove trailing slash from base if present
        if (!resultBase.empty() && resultBase.back() == '/')
            resultBase.pop_back();

        result = resultBase + "/" + url;
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