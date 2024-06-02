#ifndef ALARMCLOCK_H
#define ALARMCLOCK_H

#include <vector>
#include <thread>
#include <mutex>

class AlarmClock {
private:
    std::mutex mtx;
    std::vector<std::thread> threads;
    bool running;

public:
    AlarmClock();
    void shellProcess(int sleepTime);
    void monitorProcess(int interval);
    void startShell(int sleepTime);
    void startMonitor(int interval);
    void stop();
};

#endif // ALARMCLOCK_H

