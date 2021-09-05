#include "Producer.h"

static void* Producer::produce(void *args){
    while(!stop){
        sem_wait(&semaphore_empty_container);

        pthread_mutex_lock(&mutex_buff);
        products_containter.push_front(Product(rand() % 1500, product_type[rand() % 4]));
        statistics_produced_amount++;
        pthread_mutex_unlock(&mutex_buff);

        sem_post(&semaphore_full_container);
        }    
    }