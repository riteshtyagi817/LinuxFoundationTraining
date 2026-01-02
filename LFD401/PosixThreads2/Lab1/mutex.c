#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

#define ErrMsg(msg) { perror(msg);exit(errno);}

static char running = 1;
static long long counter = 0;

pthread_mutex_t c_mutex;

/* This is the computational thread */

void *process(void *){

	while(running){
		pthread_mutex_lock(&c_mutex);
		counter++;
		pthread_mutex_unlock(&c_mutex);
	}
	pthread_exit(NULL);
}
/* This is the user interface thread */
int main(int argc, char *argv[]){
	int i;
	pthread_t threadId;
	void *retVal;

	/* Initialize a mutex with default attributes */
	pthread_mutex_init(&c_mutex, NULL);

	/* Start up the processing thread */
	if(pthread_create(&threadId, NULL, process, "0"))
		ErrMsg("pthread_create");
	
	for(i = 0; i < 10;i++)
	{
		sleep(1);
		pthread_mutex_lock(&c_mutex);
		printf("Counter value %llu\n",counter);
		pthread_mutex_unlock(&c_mutex);
	}
	running  = 0;
	if(pthread_join(threadId, &retVal))
		ErrMsg("pthread_join")
	
	
	
	exit(EXIT_SUCCESS);
}
