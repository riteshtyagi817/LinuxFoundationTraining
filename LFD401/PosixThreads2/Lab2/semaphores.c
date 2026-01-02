#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>
#include<semaphore.h>

#define ErrMsg(msg) { perror(msg); exit(errno); }

static char running = 1;
static long long counter = 0;

sem_t c_sem;

/* This is the computational thread */
void *process(void *arg){

	while(running){
		sem_wait(&c_sem);
		counter++;
		sem_post(&c_sem);
	}
	pthread_exit(NULL);

}
/* This is the user interface thread */
int main(int argc, char *argv[]){

	int i;
	pthread_t threadId;
	void *retVal;

	/* Initialize a semaphore up */
	sem_init(&c_sem, 0, 1);

	/* start up the processing thread */
	if(pthread_create(&threadId, NULL, process, NULL))
		ErrMsg("pthread_create")
	/* look  at the counter and print out */
	for(i = 0; i < 10;i++){

		sleep(1);
		sem_wait(&c_sem);
		printf("The counter value %lld\n", counter);
		sem_post(&c_sem);
	}
	/* Tell the processing thread to quit */
	running  = 0;
	/* Wait for the processing thread to quit */
	if(pthread_join(threadId, &retVal))
		ErrMsg("pthread_join")
	
	exit(EXIT_SUCCESS);
}

