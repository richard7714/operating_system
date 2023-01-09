#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void *runner(void *param)
{
    printf("I am a thread\n");
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    int i;
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;
    /* get the deafult attributes */
    pthread_attr_init(&attr);
    /* set the scheduling algorithm to PROCESS or SYSTEM */
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setschedpolicy(&attr, SCHED_OTHER);

    for(i=0; i<NUM_THREADS;i++)
        pthread_create(&tid[i],&attr,runner,NULL);
    
    for(i=0;i<NUM_THREADS;i++)
        pthread_join(tid[i],NULL);
}