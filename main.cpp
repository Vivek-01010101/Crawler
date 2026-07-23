
#include "include/Crawler.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main()
{
Crawler crawler;
std::string url;

std::cout << "=====================================\n";
std::cout << " Simple Web Crawler\n";
std::cout << "=====================================\n";
std::cout << "Enter the Seed URL\n";
std::cout << "Format: https://example.com\n";
std::cout << "Example: https://quotes.toscrape.com\n\n";
std::cout << "URL: ";

std::getline(std::cin, url);

// Convert user input to lowercase
std::transform(url.begin(), url.end(), url.begin(),
[](unsigned char c)
{
return std::tolower(c);
});

if (url.empty())
{
std::cout << "\nError: URL cannot be empty.\n";
return 1;
}

crawler.crawl(url);

return 0;
}