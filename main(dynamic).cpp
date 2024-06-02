#include <iostream>
#include "DynamicQueue.h"

int main() {
    DynamicQueue dq;

    dq.enqueue("Process1");
    dq.enqueue("Process2");

    dq.printQueue();

    std::cout << "Dequeued: " << dq.dequeue() << std::endl;

    dq.printQueue();

    dq.enqueue("Process3");
    dq.enqueue("Process4");

    dq.printQueue();

    dq.promote();

    dq.printQueue();

    return 0;
}
