#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>

#define ErrMsg(msg) { perror(msg);exit(errno); }

volatile char running = 1;
volatile static long long counter = 0; /* if not volatile , won't work when optimization 
					  is turned on */

/* This is the computational thread */
void *processFunc(void *arg){

	while(running){

		counter++;
	}
	pthread_exit(NULL);
}
int main(int argc, char *argv[]){

	int i;
	pthread_t threadId;
	void *retVal;
	
	if(pthread_create(&threadId, NULL, processFunc, "0"))
		ErrMsg("pthread_create")
	
	for(i = 0; i < 10;i++){
		sleep(1);
		printf("%lld\n",counter);
	}
	running = 0;
	if(pthread_join(threadId, &retVal))
		ErrMsg("pthread_join")
	
	exit(EXIT_FAILURE);

}
