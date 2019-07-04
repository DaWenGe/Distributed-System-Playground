from threading import Thread, Condition
from collections import deque
import time
import random

queue = deque()
condition = Condition()

class ProducerThread(Thread):
    def run(self):
        nums = range(5)
        while True:
            condition.acquire()
            num = random.choice(nums)
            queue.append(num)
            print("Produced", num)
            condition.notify()
            condition.release()
            time.sleep(random.random())
            
class ConsumerThread(Thread):
    def run(self):
        while True:
            condition.acquire()
            if not queue:
                print("Nothing in queue, consumer is waiting...")
                condition.wait()
                print("Producer added something to queue and notified the consumer")
            num = queue.popleft()
            print("Consumed", num)
            condition.release()
            time.sleep(random.random())

ProducerThread().start()
ConsumerThread().start()