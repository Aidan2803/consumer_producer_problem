#ifndef PROCESS_H
#define PROCESS_H

class Process{
    private:
    short consumers_threads_amount;     // amount of consumer threads
    short producers_threads_amount;     // amount of producer threads
    const int threads_amount;           // total amount of threads

    pthread_t *threads;//[threads_amount];  // array of threads (consumer and producer)
    Consumer consumer;
    Producer producer;

    public:
    Process(int consumers_amount, int producers_amount, Consumer& cons, Producer& prod) : 
    consumers_threads_amount(consumers_amount), producers_threads_amount(producers_amount),
    threads_amount(consumers_amount + producers_amount), consumer(cons), producer(prod){
        threads = new pthread_t[threads_amount];
    }

    ~Process();
    
    void create_threads();

    static void signalHandler( int signumb );
};

#endif