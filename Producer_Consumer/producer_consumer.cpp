// Producer-Consumer Problem using Semaphores
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <deque>
#include <vector>
using namespace std;

// Counting semaphore built from a mutex and a condition variable
class Semaphore {
    int count;
    mutex mtx;
    condition_variable cv;
public:
    Semaphore(int value) : count(value) {}
    void acquire() {                       // wait / P operation
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this] { return count > 0; });
        count--;
    }
    void release() {                       // signal / V operation
        lock_guard<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
};

deque<int> buffer;
const int capacity = 3;
vector<int> items = {1, 2, 3, 4, 5};

Semaphore emptySlots(capacity);   // counts empty slots
Semaphore fullSlots(0);           // counts filled slots
Semaphore mutexSem(1);            // mutual exclusion on the buffer

void printBuffer() {
    cout << "[";
    for (size_t i = 0; i < buffer.size(); i++)
        cout << buffer[i] << (i + 1 < buffer.size() ? ", " : "");
    cout << "]" << endl;
}

void producer() {
    for (int item : items) {
        emptySlots.acquire();
        mutexSem.acquire();
        buffer.push_back(item);
        cout << "Produced: " << item << " Buffer: ";
        printBuffer();
        mutexSem.release();
        fullSlots.release();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer() {
    for (size_t i = 0; i < items.size(); i++) {
        fullSlots.acquire();
        mutexSem.acquire();
        int item = buffer.front();
        buffer.pop_front();
        cout << "Consumed: " << item << " Buffer: ";
        printBuffer();
        mutexSem.release();
        emptySlots.release();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main() {
    thread p(producer);
    thread c(consumer);
    p.join();
    c.join();
    cout << "All items produced and consumed." << endl;
    cout << "Final buffer: ";
    printBuffer();
    return 0;
}
