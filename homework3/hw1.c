#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_t tid[2];
int process_count;

void* execute(void* arg)
{
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    process_count += 1;
    printf("\n Process %d has started\n", process_count);
    for(i=0;i<(0xFFFFFFFF); i++)
        ;
    printf("\n Process %d has finished\n", process_count);

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    int i = 0;
    int error;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    while (i < 2){
        error = pthread_create(&(tid[i]), NULL, &execute, NULL);
        if(error != 0)
            printf("\nThread can't be created:[%s]", strerror(error));
            i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}