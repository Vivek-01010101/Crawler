#include "../../include/LinkExtractor.h"
#include "../../include/URLNormalizer.h"

LinkExtractor::LinkExtractor()
{
}

void LinkExtractor::extractLinks(const std::string& html,
                                 const std::string& baseURL,
                                 Frontier& frontier,
                                 int currentDepth)
{
    URLNormalizer normalizer;

    size_t pos = 0;

    while (true)
    {
        // Find href="
        pos = html.find("href=\"", pos);

        if (pos == std::string::npos)
            break;

        // Move past href="
        pos += 6;

        // Find closing quote
        size_t end = html.find("\"", pos);

        if (end == std::string::npos)
            break;

        // Extract URL
        std::string url = html.substr(pos, end - pos);

        // Ignore empty, javascript, mailto, tel and page anchors
        if (url.empty() ||
            url.find("javascript:") == 0 ||
            url.find("mailto:") == 0 ||
            url.find("tel:") == 0 ||
            url[0] == '#')
        {
            pos = end + 1;
            continue;
        }

        // Ignore CSS, JS, Images, PDFs
        if (url.find(".css") != std::string::npos ||
            url.find(".js") != std::string::npos ||
            url.find(".png") != std::string::npos ||
            url.find(".jpg") != std::string::npos ||
            url.find(".jpeg") != std::string::npos ||
            url.find(".gif") != std::string::npos ||
            url.find(".svg") != std::string::npos ||
            url.find(".ico") != std::string::npos ||
            url.find(".pdf") != std::string::npos)
        {
            pos = end + 1;
            continue;
        }

        // Normalize URL
        url = normalizer.normalize(baseURL, url);

        std::string seedDomain = normalizer.getDomain(baseURL);

            if (url.find(seedDomain) != 0)
            {
                pos = end + 1;
                continue;
            }

        // Add to frontier
        frontier.push(URLDepth(url, currentDepth + 1));

        pos = end + 1;
    }
}