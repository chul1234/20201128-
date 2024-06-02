#ifndef DYNAMICQUEUE_H
#define DYNAMICQUEUE_H

#include <string>
#include <deque>
#include <utility>

class DynamicQueue {
public:
    void enqueue(const std::string& process);
    std::string dequeue();
    void promote();
    void printQueue();
private:
    std::deque<std::string> DQ; // Dynamic Queue
    std::deque<std::pair<std::string, int>> WQ; // Wait Queue
};

#endif // DYNAMICQUEUE_H

