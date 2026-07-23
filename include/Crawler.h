#ifndef CRAWLER_H
#define CRAWLER_H

#include <string>

#include "Frontier.h"
#include "Fetcher.h"
#include "LinkExtractor.h"
#include "SeenStore.h"
#include "PageStorage.h"

class Crawler
{
private:
    Frontier frontier;
    Fetcher fetcher;
    LinkExtractor extractor;
    SeenStore seen;
    PageStorage storage;

public:
    Crawler();

    void crawl(const std::string& seedURL);
};

#endif