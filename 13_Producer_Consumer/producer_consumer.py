# Producer-Consumer Problem using Semaphores

import threading
import time

buffer = []
capacity = 3
items = [1, 2, 3, 4, 5]

empty = threading.Semaphore(capacity)   # counts empty slots
full = threading.Semaphore(0)           # counts filled slots
mutex = threading.Semaphore(1)          # mutual exclusion on the buffer


def producer():
    for item in items:
        empty.acquire()
        mutex.acquire()
        buffer.append(item)
        print("Produced:", item, "Buffer:", buffer)
        mutex.release()
        full.release()
        time.sleep(0.1)


def consumer():
    for _ in items:
        full.acquire()
        mutex.acquire()
        item = buffer.pop(0)
        print("Consumed:", item, "Buffer:", buffer)
        mutex.release()
        empty.release()
        time.sleep(0.2)


p = threading.Thread(target=producer)
c = threading.Thread(target=consumer)
p.start()
c.start()
p.join()
c.join()
print("All items produced and consumed.")
print("Final buffer:", buffer)
