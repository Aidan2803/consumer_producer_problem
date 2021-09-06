#include "headers/Process.h"

#include <unistd.h>

Process::~Process() {
  for (int i = 0; i < threads_amount; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("Can not join thread");
    }
  }

  delete threads;
}

void Process::run() {
  init_sync();
  create_threads();

  pthread_mutex_destroy(&mutex_buff);
}

void Process::init_sync() {
  pthread_mutex_init(&mutex_buff, NULL);
  sem_init(&semaphore_empty_container, 0, container_capacity);
  sem_init(&semaphore_full_container, 0, 0);
}

void Process::create_threads() {
  for (int i = 0; i < producers_threads_amount; i++) {
    if (pthread_create(&threads[i], NULL, *(Producer::produce), NULL) != 0) {
      perror("Could not create thread (producer)");
    }
  }

  for (int i = consumers_threads_amount; i < threads_amount; i++) {
    if (pthread_create(&threads[i], NULL, *(Consumer::consume), NULL) != 0) {
      perror("Could not create thread (consumer)");
    }
  }
}

void Process::signalHandler(int signumb) {
  stop = true;

  usleep(100000);

  std::cout << "\nProducts consumed: " << statistics_consumed_amount
            << "\nProducts produced: " << statistics_produced_amount
            << std::endl;

  exit(signumb);
}