#ifndef SYNC_CONTAINER_DATA_H
#define SYNC_CONTAINER_DATA_H

#include <semaphore.h>
#include <list>
#include <iostream>

#include "Product.h"

extern const int MAX_CAPACITY;

extern bool stop;

extern int statistics_consumed_amount;
extern int statistics_produced_amount;

extern pthread_mutex_t mutex_buff;

extern sem_t semaphore_empty_container;
extern sem_t semaphore_full_container;

extern std::string product_type[];

extern std::list<Product> products_containter;

#endif