#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <list>
#include <time.h>
#include <unistd.h>

pthread_mutex_t mutex_buff;

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
            std::cout << "id: " << id << " " << "type: " << type << "\n";
        }
};

std::list<Product> products_containter;

void* producer(void *args){
    while(1){
        pthread_mutex_lock(&mutex_buff);
        products_containter.push_front(Product(rand() % 1500, product_type[rand() % 4]));
        pthread_mutex_unlock(&mutex_buff);
    }    
}

void* consumer(void *args){
    while(1){
        pthread_mutex_lock(&mutex_buff);
        Product temp;
        temp = products_containter.back();
        products_containter.pop_back();
        temp.print_id_and_type();
        pthread_mutex_unlock(&mutex_buff);
    }    
}

int main(int argc, char* argv[]){
    srand(time(NULL));
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

    const int threads_amount = consumers_threads_amount + producers_threads_amount;

    pthread_t threads[threads_amount];
    pthread_mutex_init(&mutex_buff, NULL);

    for(int i = 0; i < producers_threads_amount; i++){
        if(pthread_create(&threads[i], NULL, *producer, NULL) != 0){
            perror("Could not create thread (producer)");
        }
    }

    for(int i = consumers_threads_amount; i < threads_amount; i++){
        if(pthread_create(&threads[i], NULL, *consumer, NULL) != 0){
            perror("Could not create thread (consumer)");
        }
    }

    for(int i = 0; i < threads_amount; i++){
        if(pthread_join(threads[i], NULL) != 0){
            perror("Can not join thread");
        }
    }

    pthread_mutex_destroy(&mutex_buff);
    return 0;
}