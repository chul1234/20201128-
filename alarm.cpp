#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "DynamicQueue2.h"

DynamicQueue dq(3, 5); // Example initialization with 3 stacks and threshold of 5
Process runningProcess(1, "B"); // Initially running process

void monitor() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        dq.displayWithRunning(runningProcess);
        std::cout << "WQ: []" << std::endl;
    }
}

void shell() {
    std::string command;
    while (true) {
        std::getline(std::cin, command);
        if (command == "exit") {
            break;
        }
        else if (command.find("enqueue") != std::string::npos) {
            std::string type = command.substr(command.find(" ") + 1);
            dq.enqueue(type);
        }
        else if (command == "dequeue") {
            runningProcess = dq.dequeue();
        }
        else if (command == "promote") {
            dq.promote();
        }
        else if (command == "split_n_merge") {
            dq.split_n_merge();
        }
    }
}

int main() {
    std::thread monitorThread(monitor);
    std::thread shellThread(shell);

    monitorThread.join();
    shellThread.join();

    return 0;
}
