// Counting Semaphore using mutex and condition variable
// Up to 3 threads can be inside the critical section at the same time.
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>
using namespace std;

mutex coutMtx;   // keeps lines printed by different threads from mixing

class Semaphore {
    int count;
    mutex mtx;
    condition_variable cv;

    void log(const string& msg, int val) {
        lock_guard<mutex> lk(coutMtx);
        cout << msg << " [Semaphore value = " << val << "]" << endl;
    }

public:
    Semaphore(int value) : count(value) {}

    int value() {
        lock_guard<mutex> lock(mtx);
        return count;
    }

    // P operation
    void wait(int id) {
        unique_lock<mutex> lock(mtx);
        while (count == 0) {
            log("Thread " + to_string(id) + " is waiting...", count);
            cv.wait(lock);
        }
        count--;
        log("Thread " + to_string(id) + " acquired semaphore", count);
    }

    // V operation
    void signal(int id) {
        unique_lock<mutex> lock(mtx);
        count++;
        log("Thread " + to_string(id) + " released semaphore", count);
        cv.notify_one();
    }
};

Semaphore sem(3);   // counting semaphore: 3 instances of the resource

void logMsg(const string& msg) {
    int v = sem.value();
    lock_guard<mutex> lk(coutMtx);
    cout << msg << " [Semaphore value = " << v << "]" << endl;
}

void process(int id) {
    sem.wait(id);
    logMsg("Thread " + to_string(id) + " entered critical section");
    this_thread::sleep_for(chrono::seconds(2));
    logMsg("Thread " + to_string(id) + " exited critical section");
    sem.signal(id);
}

int main() {
    thread t1(process, 1);
    thread t2(process, 2);
    thread t3(process, 3);
    thread t4(process, 4);
    thread t5(process, 5);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    return 0;
}
