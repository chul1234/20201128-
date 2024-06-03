# AI융합학과-20201128-홍성철
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include <condition_variable>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm> // <algorithm> 헤더 추가

using namespace std;

mutex mtx;
condition_variable cv;
bool stop = false;

class Process {
public:
    int pid;
    bool isFG;
    thread t;
    Process(int id, bool fg) : pid(id), isFG(fg) {}
    void run(int delay) {
        for (int i = 0; i < 10; ++i) {
            this_thread::sleep_for(chrono::milliseconds(delay));
            mtx.lock();
            cout << "Process #" << pid << (isFG ? " (FG)" : " (BG)") << ": " << i << endl;
            mtx.unlock();
        }
    }
};

// 2-1. Dynamic Queueing
class DynamicQueue {
    list<list<Process*>> stack;
public:
    void enqueue(Process* p) {
        mtx.lock();
        if (p->isFG) {
            if (stack.empty()) {
                stack.push_back(list<Process*>());
            }
            stack.front().push_back(p);
        } else {
            if (stack.empty()) {
                stack.push_back(list<Process*>());
            }
            stack.back().push_back(p);
        }
        mtx.unlock();
    }

    Process* dequeue() {
        mtx.lock();
        if (stack.empty() || stack.front().empty()) {
            mtx.unlock();
            return nullptr;
        }
        Process* p = stack.front().front();
        stack.front().pop_front();
        if (stack.front().empty()) {
            stack.pop_front();
        }
        mtx.unlock();
        return p;
    }

    void promote() {
        mtx.lock();
        if (stack.size() < 2) {
            mtx.unlock();
            return;
        }
        auto it = stack.begin();
        ++it;
        if (!it->empty()) {
            Process* p = it->front();
            it->pop_front();
            stack.front().push_back(p);
            if (it->empty()) {
                stack.erase(it);
            }
        }
        mtx.unlock();
    }

    void print() {
        mtx.lock();
        cout << "Dynamic Queue: ";
        for (auto& q : stack) {
            for (auto& p : q) {
                cout << p->pid << (p->isFG ? "F" : "B") << " ";
            }
        }
        cout << endl;
        mtx.unlock();
    }
};

DynamicQueue dynamicQueue;

void worker(int id, int delay) {
    for (int i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::milliseconds(delay));
        mtx.lock();
        cout << "thread#" << id << ": " << i << endl;
        mtx.unlock();
    }
}

// 2-2. Alarm Clock
void monitor(int interval) {
    while (!stop) {
        this_thread::sleep_for(chrono::seconds(interval));
        mtx.lock();
        cout << "Monitor Output:" << endl;
        dynamicQueue.print();
        mtx.unlock();
    }
}

// 2-3. Shell Command Processor
void shell(int interval) {
    ifstream commandsFile("commands.txt");
    string line;
    while (getline(commandsFile, line)) {
        istringstream iss(line);
        string command;
        while (iss >> command) {
            if (command == "echo") {
                string msg;
                iss >> msg;
                cout << msg << endl;
            } else if (command == "dummy") {
                // Dummy process, do nothing
            } else if (command == "gcd") {
                int x, y;
                iss >> x >> y;
                while (y != 0) {
                    int r = x % y;
                    x = y;
                    y = r;
                }
                cout << "GCD: " << x << endl;
            } else if (command == "prime") {
                int x;
                iss >> x;
                vector<bool> isPrime(x + 1, true);
                isPrime[0] = isPrime[1] = false;
                for (int i = 2; i * i <= x; ++i) {
                    if (isPrime[i]) {
                        for (int j = i * i; j <= x; j += i) {
                            isPrime[j] = false;
                        }
                    }
                }
                int count = count_if(isPrime.begin(), isPrime.end(), [](bool v) { return v; });
                cout << "Prime count: " << count << endl;
            } else if (command == "sum") {
                int x;
                iss >> x;
                long long sum = (static_cast<long long>(x) * (x + 1)) / 2; // long long 타입 사용
                cout << "Sum: " << sum % 1000000 << endl;
            }
        }
        this_thread::sleep_for(chrono::seconds(interval));
    }
    commandsFile.close();
}

int main() {
    thread monitorThread(monitor, 2); // Monitor every 2 seconds
    thread shellThread(shell, 5); // Shell command every 5 seconds

    Process* p1 = new Process(0, true);
    Process* p2 = new Process(1, false);

    dynamicQueue.enqueue(p1);
    dynamicQueue.enqueue(p2);

    p1->t = thread(&Process::run, p1, 1000);
    p2->t = thread(&Process::run, p2, 300);

    p1->t.join();
    p2->t.join();

    stop = true;
    cv.notify_all();
    monitorThread.join();
    shellThread.join();

    cout << "===end of main()===" << endl;
    return 0;
}
