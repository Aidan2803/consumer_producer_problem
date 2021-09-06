#ifndef PRODUCER_H
#define PRODUCER_H

#include <iostream>
#include <unistd.h>

#include "Sync_Container_data.h"
#include "Product.h"

class Producer{
    private:
    
    public:
    Producer(){}
    static void* produce(void *args);
};

#endif
