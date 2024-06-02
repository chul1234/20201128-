#include "DynamicQueue.h"
#include <iostream>
#include <algorithm>

void DynamicQueue::enqueue(const std::string& process) {
    DQ.push_back(process);
    std::cout << "Enqueued: " << process << std::endl;
}

std::string DynamicQueue::dequeue() {
    if (DQ.empty()) {
        return "Queue is empty";
    }
    std::string process = DQ.front();
    DQ.pop_front();
    return process;
}

void DynamicQueue::promote() {
    if (!WQ.empty()) {
        std::pair<std::string, int> promotedProcess = WQ.front();
        WQ.pop_front();
        DQ.push_back(promotedProcess.first + "*");
        std::cout << "Promoted: " << promotedProcess.first << std::endl;
    }
    else {
        std::cout << "No process to promote" << std::endl;
    }
}

void DynamicQueue::printQueue() {
    std::cout << "Dynamic Queue (DQ): ";
    for (const auto& process : DQ) {
        std::cout << process << " ";
    }
    std::cout << std::endl;

    std::cout << "Wait Queue (WQ): ";
    for (const auto& process : WQ) {
        std::cout << "[" << process.first << ":" << process.second << "] ";
    }
    std::cout << std::endl;
}
