from threading import Thread
import queue
import random
import time

queue = queue.Queue(10)

class ProducerThread(Thread):
    def run(self):
        nums = range(5)
        while True:
            num = random.choice(nums)
            queue.put(num)
            print("Produced", num)
            time.sleep(random.random())

class ConsumerThread(Thread):
    def run(self):
        while True:
            num = queue.get()
            queue.task_done()
            print("Consumed", num)
            time.sleep(random.random())

ProducerThread().start()
ConsumerThread().start()