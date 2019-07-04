from threading import Thread, Condition
from collections import deque
import random
import time

queue = deque()
MAX_SIZE = 10
condition = Condition()

class ProducerThread(Thread):
    def run(self):
        while True:
            nums = range(5)
            condition.acquire()
            if len(queue) >= MAX_SIZE:
                print("queue is full, waiting for consumer to consume first...")
                condition.wait()
                print("Consumer consumed something, queue is not full anymore.")
            num = random.choice(nums)
            print("Produced", num)
            queue.append(num)
            condition.notify()
            condition.release()
            time.sleep(random.random())

class ConsumerThread(Thread):
    def run(self):
        while True:
            condition.acquire()
            if not queue:
                print("queue is empty, waiting for producer to produce first...")
                condition.wait()
                print("Producer produced something, queue is not empty anymore.")
            num = queue.popleft()
            print("Consumed", num)
            condition.notify()
            condition.release()
            time.sleep(random.random())

ProducerThread().start()
ConsumerThread().start()