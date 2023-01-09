#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define LOOPS 2
#define NUMB_THREADS 3

pthread_t thr[3];
int data[100], global_index;

typedef struct _rwlock_t 
{
	sem_t lock; // binary semaphore (basic lock)
	sem_t writelock; // allow ONE writer/MANY readers
	int readers; // #readers in critical section
} rwlock_t;
rwlock_t lock;

void rwlock_init(rwlock_t *rw){
	rw->readers=0;
	sem_init(&rw->lock, 0, 1);
	sem_init(&rw->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw) {
	sem_wait(&rw->lock);
	rw->readers++;
	if(rw->readers == 1)  // first reader gets writelock
		sem_wait(&rw->writelock);
	sem_post(&rw->lock);
}
void rwlock_release_readlock(rwlock_t *rw) {
	sem_wait(&rw->lock);
	rw->readers--;
	if(rw->readers == 0)
		sem_post(&rw->writelock);
	sem_post(&rw->lock);
}
void rwlock_acquire_writelock(rwlock_t *rw) {
	sem_wait(&rw->writelock);
}
void rwlock_release_writelock(rwlock_t *rw) {
	sem_post(&rw->writelock);
}

void *writer(void *arg) {
	int thread_numb = *(int *) arg;
	int i = 0;

	while(1)
	{
		sleep(1);
		srand((int)time(NULL)); // Use time as a seed for random number
		rwlock_acquire_writelock(&lock); 
		int value = rand() % 100; 
		if(global_index > 100)
		{ 
			break;
		}
		data[global_index] = value; // input random number into data[global_index]
		printf("\n ###########data updated############\n");
		printf("writer %d writes %d at global : %d\n", thread_numb, value, global_index);
		global_index++; // update global_index
		rwlock_release_writelock(&lock);
	}
	pthread_exit(0);

}

void *reader(void *arg) {
	int thread_numb = *(int *) arg;
	int i = 0;

	while(1)
	{
		sleep(1);
		rwlock_acquire_readlock(&lock);
		if(global_index>0)
		{
			printf("reader %d reads %d at global : %d\n", thread_numb, data[global_index-1], global_index-1);
		}

		else
		{
			printf("reader %d reads %d at global : %d\n", thread_numb, data[global_index], global_index);
		}

		rwlock_release_readlock(&lock);
	}
	pthread_exit(0);
}

void main() {
	rwlock_init(&lock);
	memset(data, 0, sizeof(data));
	global_index = 0;
	
	pthread_t thread[NUMB_THREADS];
	int thread_numb[NUMB_THREADS];

	thread_numb[0] = 0;
	pthread_create(thread, NULL,writer,thread_numb);

	thread_numb[1] = 1;
	pthread_create(&thread[1], NULL, reader, &thread_numb[1]);

	thread_numb[2] = 2;
	pthread_create(&thread[2], NULL, reader, &thread_numb[2]);

	for(int i=0;i<6000;i++){
		usleep(1000);
	}

	for (int i=0; i<NUMB_THREADS; i++)
		pthread_join(thread[i], NULL);
	
	return;
}
