#include "headers/Sync_Container_data.h"

const int MAX_CAPACITY = 1000;

bool stop = false;

int statistics_consumed_amount = 0;
int statistics_produced_amount = 0;
pthread_mutex_t mutex_buff;

sem_t semaphore_empty_container;
sem_t semaphore_full_container;

std::string product_type[] = {"Computer", "Vehicle", "Laptop", "E-book"};

std::list<Product> products_containter;