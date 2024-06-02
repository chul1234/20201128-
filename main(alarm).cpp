#include "AlarmClock.h"

int main() {
    AlarmClock alarmClock;

    alarmClock.startShell(2);
    alarmClock.startMonitor(3);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    alarmClock.stop();

    return 0;
}
