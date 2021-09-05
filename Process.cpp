#include "Process.h"

Process::~Process(){
    for(int i = 0; i < threads_amount; i++){
        if(pthread_join(threads[i], NULL) != 0){
            perror("Can not join thread");
        }
    }

    delete threads;
}

void Process::create_threads(){
    for(int i = 0; i < producers_threads_amount; i++){
        if(pthread_create(&threads[i], NULL, *(Producer::produce), NULL) != 0){
            perror("Could not create thread (producer)");
        }
    }

    for(int i = consumers_threads_amount; i < threads_amount; i++){
        if(pthread_create(&threads[i], NULL, *(Consumer::consume), NULL) != 0){
            perror("Could not create thread (consumer)");
        }
    }
}

static void signalHandler( int signumb ){
        stop = true;
        
        usleep(100000);

        std::cout << "\nProducts consumed: " << statistics_consumed_amount << "\nProducts produced: " << statistics_produced_amount << std::endl;

        exit(signumb);
    }   