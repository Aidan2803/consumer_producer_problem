#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <list>
#include <time.h>
#include <csignal>
#include <unistd.h>

#include "Process.h"

const int MAX_CAPACITY{1000};

bool stop{false};

int statistics_consumed_amount{};
int statistics_produced_amount{};

pthread_mutex_t mutex_buff;

sem_t semaphore_empty_container;
sem_t semaphore_full_container;

std::string product_type[] = {"Computer", "Vehicle", "Laptop", "E-book"};

//class Product

std::list<Product> products_containter;

//class Consumer

//class Producer

//class Process

class ProcessWrapper{
    private:
    Process *proc;
    public:
    ProcessWrapper(){
        proc = new proc();
    }
    void run(){}
    ~ProcessWrapper(){
        delete proc;
    };
};

short get_capacity(){
    char *container_capacity_to_convert = new char;
    short container_capacity;

    std::cout << "Enter max amount of elements in container\n";
    std::cin >> container_capacity_to_convert;

    container_capacity = atoi(container_capacity_to_convert);

    delete container_capacity_to_convert;
    
    return container_capacity;
}

bool check_if_data_valid(short consumers_threads_amount_to_check, short producers_threads_amount_to_check, short &capacity){
    bool failed{false};

    if(consumers_threads_amount_to_check < 0 || consumers_threads_amount_to_check > 255){
         std::cout << "Amount of consumers can not be below 0 or more than 255\n";
         failed = true;
    }
    
    if(producers_threads_amount_to_check < 0 || producers_threads_amount_to_check > 255){
         std::cout << "Amount of producers can not be below 0 or more than 255\n";
         failed = true;
    }

    short container_capacity = get_capacity();

    if(container_capacity == 0){
        std::cout << "Invalid value, must be from 1 to " << MAX_CAPACITY << "\n";
        failed = true;
    }

    capacity = container_capacity;
    
    return failed;
}

int main(int argc, char* argv[]){
    signal(SIGINT, Process::signalHandler);
    srand(time(NULL));    

    bool fault{false};

    if(argc < 3){
        std::cout << "Incorrect usage of program! Use: ./CPP amount_of_consumers amount_of_producers\n" <<
        "Example: ./CPP 3 6\n";
        return 0;
    }

    short consumers_threads_amount_from_terminal{};
    short producers_threads_amount_from_terminal{};
    short container_capacity{};

    consumers_threads_amount_from_terminal = atoi(argv[1]);
    producers_threads_amount_from_terminal = atoi(argv[2]);

    if(check_if_data_valid(consumers_threads_amount_from_terminal, producers_threads_amount_from_terminal, container_capacity)){
        return 0;
    }  
    
    Producer prod;
    Consumer cons;
    Process proc(consumers_threads_amount_from_terminal, producers_threads_amount_from_terminal, cons, prod);
    
    pthread_mutex_init(&mutex_buff, NULL);
    sem_init(&semaphore_empty_container, 0, container_capacity);
    sem_init(&semaphore_full_container, 0, 0);

    proc.create_threads();
    
    pthread_mutex_destroy(&mutex_buff);

    return 0;
}