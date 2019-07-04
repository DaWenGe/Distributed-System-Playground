from threading import Thread, Lock
from collections import deque
import time
import random

queue = deque()
lock = Lock()

class ProducerThread(Thread):
    def run(self):
        nums = range(5)
        while True:
            num = random.choice(nums)
            lock.acquire()
            queue.append(num)
            print ("Produced", num)
            lock.release()
            time.sleep(random.random())

class ConsumerThread(Thread):
    def run(self):
        while True:
            lock.acquire()
            if not queue:
                print ("Nothing in queue, but consumer will try to consume")
            num = queue.popleft()
            print ("Consumed", num)
            lock.release()
            time.sleep(random.random())

ProducerThread().start()
ConsumerThread().start()