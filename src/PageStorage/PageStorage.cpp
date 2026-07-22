#include "../../include/PageStorage.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

PageStorage::PageStorage(const std::string& dir) 
    : storageDir(dir), nextId(1) {
    ensureDirectoryExists();
}

PageStorage::~PageStorage() {}

void PageStorage::ensureDirectoryExists() const {
    struct stat st;
    if (stat(storageDir.c_str(), &st) == -1) {
        mkdir(storageDir.c_str(), 0777);
    }
}

std::string PageStorage::getFilePath(int id) const {
    return storageDir + "/" + std::to_string(id);
}

void PageStorage::storePage(const std::string& url, const std::string& html, int depth) {
    if (urlToId.contains(url)) {
        return;
    }
    
    int id = nextId++;
    urlToId.put(url, id);
    
    std::string filePath = getFilePath(id);
    std::ofstream file(filePath);
    
    if (file.is_open()) {
        file << url << "\n";
        file << depth << "\n";
        file << html;
        file.close();
    } else {
        std::cerr << "Error: Could not open file: " << filePath << std::endl;
    }
}

std::string PageStorage::getPage(const std::string& url) const {
    if (!urlToId.contains(url)) {
        return "";
    }
    
    int id = urlToId.get(url);
    std::string filePath = getFilePath(id);
    std::ifstream file(filePath);
    
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        
        size_t pos = content.find('\n');
        if (pos != std::string::npos) {
            pos = content.find('\n', pos + 1);
            if (pos != std::string::npos) {
                return content.substr(pos + 1);
            }
        }
        return "";
    }
    return "";
}

bool PageStorage::hasPage(const std::string& url) const {
    return urlToId.contains(url);
}

int PageStorage::pageCount() const {
    return urlToId.size();
}