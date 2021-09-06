#ifndef PROCESS_H
#define PROCESS_H

#include "Consumer.h"
#include "Producer.h"

class Process{
    private:
    short consumers_threads_amount;     
    short producers_threads_amount;   
    short container_capacity;
    const int threads_amount; 
              
    pthread_t *threads;
    Consumer consumer;
    Producer producer;

    public:
    Process(int consumers_amount, int producers_amount, short capacity, Consumer& cons, Producer& prod) : 
    consumers_threads_amount(consumers_amount), producers_threads_amount(producers_amount),
    threads_amount(consumers_amount + producers_amount), container_capacity(capacity), consumer(cons), producer(prod){
        threads = new pthread_t[threads_amount];
    }

    ~Process();

    void run();

    void init_sync();
    
    void create_threads();

    static void signalHandler(int signumb);
};

#endif