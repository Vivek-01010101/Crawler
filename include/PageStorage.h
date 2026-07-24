#ifndef PAGESTORAGE1_H
#define PAGESTORAGE1_H

#include <string>
#include <sqlite3.h>

class PageStorage
{
public:
    PageStorage();
    ~PageStorage();

    void storePage(const std::string& url,
                   const std::string& html,
                   int depth);

    std::string getPage(const std::string& url) const;

    bool hasPage(const std::string& url) const;

    int pageCount() const;

private:
    sqlite3* db;
};

#endif