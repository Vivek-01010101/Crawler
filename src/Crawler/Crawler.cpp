#include "../../include/Crawler.h"
#include <iostream>

Crawler::Crawler()
    : storage()
{
}

void Crawler::crawl(const std::string& seedURL)
{
    frontier.push(URLDepth(seedURL, 0));

    while (!frontier.empty())
    {
        URLDepth current = frontier.pop();

        if (current.depth > 2)
            continue;

        if (seen.contains(current.url))
            continue;

        seen.insert(current.url);

        std::cout << "[" << current.depth << "] "
          << current.url << std::endl;

        std::string html = fetcher.fetch(current.url);

        if (html.empty())
            continue;

        storage.storePage(
            current.url,
            html,
            current.depth);

        extractor.extractLinks(
            html,
            current.url,
            frontier,
            current.depth);
    }

    std::cout << "\nCrawling Finished\n";
    std::cout << "Total Pages: "
              << storage.pageCount()
              << std::endl;
}