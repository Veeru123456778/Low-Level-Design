#include<bits/stdc++.h>
using namespace std;

class Counter{
    int counter; // shared resource 
    atomic<int> counterTwo{0};
    mutex mtx;

    public:
    Counter(){
        counter = 0;
    }

    void incrementCounter(){
        lock_guard<mutex> lock(mtx);

        counter++; // counter = counter+1
    }

    void incrementCounterTwo(){
       // No need to increase the counter as it is by dafult atomic through hardware

        counterTwo++; // counter = counter+1
    }

    void ProcessTask(){
        for(int i=0;i<1000000;i++){
            incrementCounter();
        }
    }

    void ProcessTaskTwo(){
        for(int i=0;i<1000000;i++){
            incrementCounterTwo();
        }
    }

    int getCount(){
        return this->counter;
    }

    int getCountTwo(){
        return this->counterTwo;
    }
};


int main(){
 Counter c;

 thread t1(&Counter::ProcessTask,&c);
 thread t2(&Counter::ProcessTask,&c);
 thread t3(&Counter::ProcessTask,&c);
 thread t4(&Counter::ProcessTask,&c);

 thread t5(&Counter::ProcessTaskTwo,&c);
 thread t6(&Counter::ProcessTaskTwo,&c);
 thread t7(&Counter::ProcessTaskTwo,&c);
 thread t8(&Counter::ProcessTaskTwo,&c);


 // thread.join() will wait for the thread to complete before exiting the main function

 t1.join();
 t2.join();
 t3.join();
 t4.join();
 t5.join();
 t6.join();
 t7.join();
 t8.join();

 cout<<c.getCount()<<endl;
 cout<<c.getCountTwo()<<endl;

 }