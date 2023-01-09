#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#define SIZE 2
#define NUMB_THREADS 4
#define LOOPS 2

typedef int buffer_t;
buffer_t buffer[SIZE];
int buffer_index;

sem_t mutex;
sem_t full;
sem_t empty;

void put(buffer_t value) {
    if (buffer_index > SIZE) {
        buffer[buffer_index++] = value;
    }
    else {
        printf("Buffer overflow\n");
    }
}

buffer_t get() {
    if (buffer_index >0) {
        return buffer[--buffer_index];
    } else{
        printf("Buffer underflow\n");
    }
    return 0;
}

void *producer(void *thread_n){
    int thread_numb = *(int *) thread_n;
    buffer_t value;
    int i = 0;
    while (i++ <LOOPS) {
        sleep(rand() % 10);
        value = rand() % 100;
        sem_wait(&full);
        sem_wait(&mutex);
        put(value);
        sem_post(&mutex);
        sem_post(&empty);
        printf("Producer %d added %d to buffer\n", thread_numb, value);
    }
}

void *consumer(void *thread_n) {
    int thread_numb = *(int *) thread_n;
    buffer_t value;
    int i =0;
    while (i++<LOOPS){
        sem_wait(&empty);
        sem_wait(&mutex);
        value = get();
        sem_post(&mutex);
        sem_post(&full);
        printf("Consumer %d dequeue %d from buffer\n", thread_numb, value);
    }
    pthread_exit(0);
}

int main(int argc, int **argv) {
    buffer_index = 0;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, SIZE);
    sem_init(&empty, 0, 0);

    pthread_t thread[NUMB_THREADS];
    int thread_numb[NUMB_THREADS];
    int i;
    for (i = 0; i< NUMB_THREADS; ) {
        thread_numb[i] = i;
        pthread_create(thread+i,NULL, producer, thread_numb+i);
        i++;
        thread_numb[i] = i;

        pthread_create(&thread[i], NULL, consumer, &thread_numb[i]);
        i++;

    }

    for (i=0; i<NUMB_THREADS; i++)
        pthread_join(thread[i], NULL);
    
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    
    return 0;

}