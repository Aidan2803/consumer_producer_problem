#ifndef CONSUMER_H
#define CONSUMER_H

#include <iostream>
#include <unistd.h>

#include "Sync_Container_data.h"
#include "Product.h"

class Consumer{
    private:

    public:
    Consumer(){}
    static void* consume(void *args);
};

#endif