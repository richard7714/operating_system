#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 2
#define NUMB_THREADS 4
#define LOOPS 2

// Declare buffer
typedef int buffer_t;
buffer_t buffer[SIZE];
int buffer_index;

// Declare semaphore
sem_t mutex;
sem_t full;
sem_t empty;

// Buffer input function
void put(buffer_t value){
    if (buffer_index < SIZE) {
        buffer[buffer_index++] = value;
    }
    else {
        printf("Buffer overflow\n");
    }
}

// Buffer output function
buffer_t get() {
    if (buffer_index > 0) {
        return buffer[--buffer_index];
    } else {
        printf("Buffer underflow\n");
    }
    return 0;
}

// Function for producer
void *producer(void *thread_n) {
    int thread_numb = *(int *)thread_n;
    buffer_t value;
    int i=0;
    while (i++ < LOOPS) {
        sleep(rand() % 10);
        value = rand() % 100;
        // lock semaphore
        sem_wait(&full);
        sem_wait(&mutex);
        put(value);
        // release semmaphore
        sem_post(&mutex);
        sem_post(&empty);
        printf("Producer %d added %d to buffer\n", thread_numb, value);
    }
    pthread_exit(0);
}

void *consumer(void *thread_n) {
    int thread_numb = *(int *)thread_n;
    buffer_t value;
    int i =0;
    while (i++<LOOPS) {
        // lock semaphore
        sem_wait(&empty);
        sem_wait(&mutex);
        value = get(value);
        // release semaphore
        sem_post(&mutex);
        sem_post(&full);
        printf("Consumer %d dequeue %d from buffer\n", thread_numb, value);
    }
    pthread_exit(0);
}

int main(int argc, int **argv){
    buffer_index = 0;

    // intialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, SIZE);
    sem_init(&empty, 0, 0);

    // initalize threads
    pthread_t thread[NUMB_THREADS];
    int thread_numb[NUMB_THREADS];
    int i;
    for (i=0;i<NUMB_THREADS; ){
        // thread for producer
        thread_numb[i] = i;
        pthread_create(thread + i, NULL, producer, thread_numb + i);
        i++;
        thread_numb[i] = i;

        // thread for consumer
        pthread_create(&thread[i], NULL, consumer, &thread_numb[i]);
        i++;
    }

    for (i=0; i< NUMB_THREADS; i++)
        pthread_join(thread[i], NULL);

    // destroy semaphore
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}