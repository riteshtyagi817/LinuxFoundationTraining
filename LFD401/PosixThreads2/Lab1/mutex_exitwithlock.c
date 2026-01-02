#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>
#define ErrMsg(msg) { perror(msg); exit(errno);}

static char running = 1;
static long long counter = 0;

pthread_mutex_t c_mutex;
int i;

/* This is the computational thread */

void *process(void *arg){


	while(running){

		pthread_mutex_lock(&c_mutex);
		if(i > 4) 
			pthread_exit(NULL);
		counter++;
		pthread_mutex_unlock(&c_mutex);
	}
	pthread_exit(NULL);
}
int main(int argc, char *argv[]){



	pthread_t threadId;
	void *retVal;

	/* Initialize a mutex with default attributes */

	pthread_mutex_init(&c_mutex, NULL);
	
	/* start up the processing thread */
	if(pthread_create(&threadId, NULL, process, "0"))
		ErrMsg("pthread_create")
	
	/* look at the counter at some time */
	
	for(i = 0; i  < 10;i++){
		sleep(1);
		pthread_mutex_lock(&c_mutex);
		printf("The counter value is %llu.\n",counter);
		pthread_mutex_unlock(&c_mutex);
	}
	/* Tell the processing thread to quit */
	running = 0;

	if(pthread_join(threadId, &retVal))
		ErrMsg("pthread_join")

	exit(EXIT_SUCCESS);

}
