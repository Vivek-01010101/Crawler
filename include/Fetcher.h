#ifndef FETCHER_H
#define FETCHER_H

#include <string>

class Fetcher
{
public:
    Fetcher();
    ~Fetcher();

    std::string fetch(const std::string& url);

private:
    static size_t writeCallback(
        void* contents,
        size_t size,
        size_t nmemb,
        void* userp);
};

#endif