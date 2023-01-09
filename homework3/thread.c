// header files

pthread_t tid[2];
int process_count;

void* execute(void* arg)
{
	unsigned long i = 0;
	process_count += 1;
	printf ("\n Process %d has started\n", process_count);
	for (i = 0; i<(0xFFFFFFFF);i++)
		;
	printf("\n Process %d has finished\n", process_count);
	return NULL;
}

int main(void)
{
	int i = 0;
	int error;

	while (i<2){
		error = pthread_create(&(tid[i], NULL, &execute,NULL);
		if(error !=0)	
			printf("\nThread can't be created:[%s]", strerror(error));
			i++;
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
