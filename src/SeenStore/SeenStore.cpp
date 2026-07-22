#include "../../include/SeenStore.h"

SeenStore::SeenStore() {}

bool SeenStore::contains(const std::string& url) const {
    return seen.contains(url);
}

void SeenStore::insert(const std::string& url) {
    seen.put(url, true);
}

int SeenStore::count() const {
    return seen.size();
}