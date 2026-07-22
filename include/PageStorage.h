#ifndef PAGESTORAGE_H
#define PAGESTORAGE_H

#include <string>
#include "/Users/vivek/Downloads/CodeQuotient/DS_LIBRARY-VIVEK/include/HashMap.h"

class PageStorage {
public:
    PageStorage(const std::string& storageDir);
    ~PageStorage();
    
    void storePage(const std::string& url, const std::string& html, int depth);
    std::string getPage(const std::string& url) const;
    bool hasPage(const std::string& url) const;
    int pageCount() const;

private:
    std::string storageDir;
    HashMap<std::string, int> urlToId;
    int nextId;
    
    std::string getFilePath(int id) const;
    void ensureDirectoryExists() const;
};

#endif