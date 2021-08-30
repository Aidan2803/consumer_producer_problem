#include <iostream>
#include <semaphore.h>
#include <pthread.h>

int main(int argc, char* argv[]){
    short consumers_threads_amount{};
    short producers_threads_amount{};

    bool fault{false};

    if(argc < 3){
        std::cout << "Incorrect usage of program! Use: ./CPP amount_of_consumers amount_of_producers\n" <<
        "Example: ./CPP 3 6\n";
        return 0;
    }

    consumers_threads_amount = atoi(argv[1]);
    producers_threads_amount = atoi(argv[2]);
    
    if(consumers_threads_amount < 0 || consumers_threads_amount > 255){
         std::cout << "Amount of consumers can not be below 0 or more than 255\n";
         fault = true;
    }
    
    if(producers_threads_amount < 0 || producers_threads_amount > 255){
         std::cout << "Amount of producers can not be below 0 or more than 255\n";
         fault = true;
    }

    if(fault){return 0;}

    

    return 0;
}