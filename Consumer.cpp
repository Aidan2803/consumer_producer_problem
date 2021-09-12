#include "headers/Consumer.h"

void* Consumer::consume(void* args) {
  while (!stop) {
    sem_wait(&semaphore_full_container);

    pthread_mutex_lock(&mutex_buff);
    usleep(1000);
    Product temp;
    temp = products_containter.back();
    products_containter.pop_back();
    temp.print_id_and_type();
    statistics_consumed_amount++;
    pthread_mutex_unlock(&mutex_buff);

    sem_post(&semaphore_empty_container);
  }
}