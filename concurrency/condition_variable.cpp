#include<bits/stdc++.h>
using namespace std;

/*

Usage: cv.wait(lock,lambda function) (In lambda function we give the condition if condition is true then the thread reacquires the lock , if it is false it releasees the lock and goes to sleep and wakes up if any other thread notifies it through cv.notify_one() or cv.notify_all())

// This is exactly what cv.wait(lock, lambda) does internally:
while (!condition_is_met()) {
    cv.wait(lock); // 1. Release lock & Sleep 
                   // 2. Wake up on notification & Re-acquire lock
}

The Problem without Condition Variables: "Busy-Waiting" (Polling)
Imagine Thread A needs to read data from a queue, but the queue is currently empty. Without a condition variable, Thread A must do this:

C++
// ❌ WRONG: Heavy CPU waste (Busy-Waiting)
while (true) {
    lock_guard<mutex> lock(mtx);
    if (!queue.empty()) {
        auto item = queue.front();
        queue.pop();
        break;
    }
} // Mutex locked and unlocked millions of times per second!

Why this is terrible: Thread A locks and unlocks the mutex millions of times per second just to check queue.empty(). This pegs CPU usage to 100% and blocks other threads from acquiring the lock.


The Solution with std::condition_variable:

Instead of repeatedly asking "Is data ready?", Thread A releases the lock and goes to sleep until Thread B pushes data and signals/notifies Thread A to wake up.

C++
// ✅ CORRECT: 0% CPU waste while waiting
unique_lock<mutex> lock(mtx);
cv.wait(lock, []() { return !queue.empty(); }); // Releases lock & sleeps!
auto item = queue.front();
queue.pop();


Does std::condition_variable use a Mutex internally?

Yes, it strictly depends on a mutex! Specifically, it requires std::unique_lock<std::mutex>.

Here is what happens under the hood when a thread calls cv.wait(lock):


Atomic Release & Sleep: cv.wait() atomically releases the mutex and puts the calling thread into a sleeping state (WAITING state).

Notification: Another thread modifies the shared state and calls cv.notify_one() or cv.notify_all().

Re-acquire Mutex: The sleeping thread wakes up, automatically re-acquires the mutex, and verifies the condition again before continuing execution.


Why std::unique_lock instead of std::lock_guard? > std::lock_guard cannot be manually unlocked or relocked. std::unique_lock gives std::condition_variable the ability to explicitly unlock the mutex while sleeping and relock it upon waking up.

cv_producer --> 1 --> Dedicated wait line for Producers sleeping because queue is FULL.
cv_consumer --> 1 --> Dedicated wait line for Consumers sleeping because queue is EMPTY.

std::thread worker( &Consumer::backgroundProcessing ,  &c );
                    └──────────────┬──────────────┘   └──┬──┘
                            Member Function         Object Instance
                          (What code to run)       (The 'this' pointer)

                          
*/

class SharedResourceQueue{
    queue<int> shared_queue;
    int maxCapacity;
    condition_variable cv_producer;
    condition_variable cv_consumer;
    mutex mtx; // because the queue is shared between the consumer/producer so one mutex should be there 
    public:

    SharedResourceQueue(int maxCapacity){
        this->maxCapacity = maxCapacity;
    }

    bool isQueueEmpty(){
        return shared_queue.empty();
    }

    void pushMessage(int msgId){
        unique_lock<mutex> ulock(mtx);

        cv_producer.wait(ulock,[this](){
            return (shared_queue.size()<maxCapacity);
        });

        shared_queue.push(msgId);
        cout << "[Producer] Pushed message: " << msgId << endl;

        cv_consumer.notify_one();
    }

    int popMessage(){
        unique_lock<mutex> ulock(mtx);

    
        cv_consumer.wait(ulock,[this](){
           return (!shared_queue.empty());
        });

        int msgId = shared_queue.front();
        shared_queue.pop();

        cout << "[Consumer] Popped message: " << msgId << endl;

        cv_producer.notify_one();

        return msgId;
    }

    bool isQueueFull(){
        return !shared_queue.empty();
    }
};

class Consumer{
   SharedResourceQueue* q;
   public:

   Consumer(SharedResourceQueue* q){
     this->q = q;
   }

   void processMessage(int messageId){
      // processing message here....
      cout<<"Processing message "<<messageId<<endl;
   }

   void backgroundProcessing(){
      while(true){
        int msgId = q->popMessage();
        processMessage(msgId);
      }
   }
};


class Producer{
  SharedResourceQueue* queue;

  public:

  Producer(SharedResourceQueue* q){
    queue = q;
  }

  void produceMessage(int messageId){
     queue->pushMessage(messageId);
  }
};

int main(){
  SharedResourceQueue *q = new SharedResourceQueue(10);
  Consumer c(q);
  Producer p(q);

  thread worker(&Consumer::backgroundProcessing,&c);

  
  for(int i=0;i<5;i++){
    p.produceMessage(i);
    this_thread::sleep_for(chrono::milliseconds(5000));
  }

  worker.join();
}