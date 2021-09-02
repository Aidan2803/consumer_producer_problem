#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <list>
#include <time.h>
#include <csignal>
#include <unistd.h>

const int MAX_CAPACITY{1000};

bool stop{false};

int statistics_consumed_amount{};
int statistics_produced_amount{};

pthread_mutex_t mutex_buff;

sem_t semaphore_empty_container;
sem_t semaphore_full_container;

std::string product_type[] = {"Computer", "Vehicle", "Laptop", "E-book"};

class Product{
    private:
        int id;
        std::string type;
    public:
        Product():id(0), type("NONE"){}
        Product(int newId, std::string newType):id(newId), type(newType){}
        ~Product(){};
    
        void print_id_and_type(){
            std::cout << "id: " << id << " type: " << type << "\n";
        }
};

std::list<Product> products_containter;

class Consumer{
    private:

    public:
    Consumer(){}
    static void* consume(void *args){
        while(!stop){
            sem_wait(&semaphore_full_container);

            pthread_mutex_lock(&mutex_buff);
            Product temp;
            temp = products_containter.back();
            products_containter.pop_back();
            temp.print_id_and_type();
            statistics_consumed_amount++;
            pthread_mutex_unlock(&mutex_buff);

            sem_post(&semaphore_empty_container);
        }    
    }
};

class Producer{
    private:
    
    public:
    Producer(){}
    static void* produce(void *args){
    while(!stop){
        sem_wait(&semaphore_empty_container);

        pthread_mutex_lock(&mutex_buff);
        products_containter.push_front(Product(rand() % 1500, product_type[rand() % 4]));
        statistics_produced_amount++;
        pthread_mutex_unlock(&mutex_buff);

        sem_post(&semaphore_full_container);
    }    
}
};

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

    ~Process(){
        for(int i = 0; i < threads_amount; i++){
            if(pthread_join(threads[i], NULL) != 0){
                perror("Can not join thread");
            }
        }

        delete threads;
    }
    
    void create_threads(){
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