#include "../../include/Frontier.h"

Frontier::Frontier() 
{
    // Queue is default constructed
}

void Frontier::push(const URLDepth& item) 
{
    queue.enqueue(item);
}

URLDepth Frontier::pop() 
{
    if (empty()) {
        // Error handling: return empty URLDepth with depth = -1
        return URLDepth();
    }
    
    URLDepth frontItem = queue.front();
    queue.dequeue();
    return frontItem;
}

bool Frontier::empty() const 
{
    return queue.empty();
}

int Frontier::size() const 
{
    return static_cast<int>(queue.size());
}