#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>

#define NUM_THREADS 10

void sighand(int sig){

	printf("I am executing signal handler in thread %lu.\n",pthread_self());

}
void * tFunc(void *arg){
	printf("Thread %lu starting\n", pthread_self());
	pause(); /* will return when any signal is received */
	printf("Thread %lu exiting\n",pthread_self());
	pthread_exit(NULL);
}
int main(int argc, char *argv[]){

	int i;
	pthread_t threads[NUM_THREADS];
	sigset_t sigmask;

	struct sigaction act;

	act.sa_handler = sighand;
	if(sigaction(SIGINT, &act, NULL)  < 0){
		printf("Failed to install signal handler.\n");
		exit(EXIT_FAILURE);
	}
	printf("Master thread id %lu\n",pthread_self());

	for(i = 0; i < NUM_THREADS;i++){
		pthread_create(&threads[i], NULL, tFunc, NULL);
		printf("Thread ID = %lu\n",threads[i]);
	}
	/* block the signal in master thread only */
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGINT);
	pthread_sigmask(SIG_BLOCK, &sigmask, NULL);

	for(i = 0; i < NUM_THREADS;i++){
		kill(getpid(), SIGINT);
		//sched_yield(); // sleep(1) will also work
		sleep(1);
	}
	// Wait for threads to terminate 
	for(i = 0; i < NUM_THREADS;i++){
		pthread_join(threads[i],NULL);
		printf("Master thread joined with thread %d\n",i);
	}

	exit(EXIT_SUCCESS);
}
