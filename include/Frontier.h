#ifndef FRONTIER_H
#define FRONTIER_H

#include <string>
#include "../external/project01/include/Queue.h"

struct URLDepth {
    std::string url;
    int depth;
    
    URLDepth() : url(""), depth(-1) {}
    URLDepth(const std::string& u, int d) : url(u), depth(d) {}
};

class Frontier {
public:
    Frontier();                    // Constructor
    void push(const URLDepth& item);      // Adds URL-depth pair to end
    URLDepth pop();                // Removes and returns from front
    bool empty() const;            // Checks if queue is empty
    int size() const;              // Returns number of pending items

private:
    Queue<URLDepth> queue;
};

#endif