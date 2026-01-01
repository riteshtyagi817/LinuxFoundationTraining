#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
void init_fun(void) __attribute__((constructor));
void exit_fun(void) __attribute__((destructor));

void init_fun(void){
	printf(" I am in %s\n",__func__);

}
void exit_fun(void){
	printf(" I am in %s\n",__func__);
}
#define ErrMsg(msg) { perror(msg);exit(errno);}
volatile char running = 1;
volatile static long long counter = 0; /* If not volatine, won't work when optimization is turned on */

/* This is the computational thread */
void *process(void *arg){

	while(running){
		counter++;	
	};
	pthread_exit(NULL);
}
/* This is the user interface thread */
int main(int agrc, char *argv[]){
	
	int i;
	pthread_t threadId;
	void *retVal;
	/* start up the processing thread */
	printf("Just before thread creation.\n");
	if(pthread_create(&threadId,NULL, process, "0"))
	       ErrMsg("pthread_create")

	for(i = 0; i < 10;i++){
		sleep(1);
		printf("Counter value %llu\n", counter);
	}
	running = 0;

	if(pthread_join(threadId, &retVal))
		ErrMsg("pthread_join")




	exit(EXIT_SUCCESS);
}
