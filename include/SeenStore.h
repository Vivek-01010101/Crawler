#ifndef SEENSTORE_H
#define SEENSTORE_H

#include <string>
#include "../external/project01/include/HashMap.h"

class SeenStore {
public:
    SeenStore();
    bool contains(const std::string& url) const;
    void insert(const std::string& url);
    int count() const;

private:
    HashMap<std::string, bool> seen;
};

#endif