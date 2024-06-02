#include "AlarmClock.h"
#include <chrono>
#include <iostream>

AlarmClock::AlarmClock() : running(true) {}

void AlarmClock::shellProcess(int sleepTime) {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Shell process executing commands...\n";
    }
}

void AlarmClock::monitorProcess(int interval) {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(interval));
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Monitoring system state...\n";
    }
}

void AlarmClock::startShell(int sleepTime) {
    threads.push_back(std::thread(&AlarmClock::shellProcess, this, sleepTime));
}

void AlarmClock::startMonitor(int interval) {
    threads.push_back(std::thread(&AlarmClock::monitorProcess, this, interval));
}

void AlarmClock::stop() {
    running = false;
    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }
}
