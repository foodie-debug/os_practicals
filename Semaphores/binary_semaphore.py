import threading
import time
print_lock = threading.Lock()
class Semaphore:
    def __init__(self, value):
        self.count = value
        self.lock = threading.Lock()
        self.cv = threading.Condition(self.lock)
    def _log(self, msg, val):
        with print_lock:
            print(msg, "[Semaphore value =", str(val) + "]")
    def value(self):
        with self.lock:
            return self.count
    def wait(self, tid):
        with self.cv:
            while self.count == 0:
                self._log("Thread " + str(tid) + " is waiting...", self.count)
                self.cv.wait()
            self.count -= 1
            self._log("Thread " + str(tid) + " acquired semaphore", self.count)
    def signal(self, tid):
        with self.cv:
            self.count += 1
            self._log("Thread " + str(tid) + " released semaphore", self.count)
            self.cv.notify()
sem = Semaphore(1)
def log_msg(msg):
    v = sem.value()
    with print_lock:
        print(msg, "[Semaphore value =", str(v) + "]")
def process(tid):
    sem.wait(tid)
    log_msg("Thread " + str(tid) + " entered critical section")
    time.sleep(2)
    log_msg("Thread " + str(tid) + " exited critical section")
    sem.signal(tid)
threads = [threading.Thread(target=process, args=(i,)) for i in range(1, 4)]
for t in threads:
    t.start()
for t in threads:
    t.join()
