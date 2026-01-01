#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>

#define NUM_THREADS 10

void *sigFunc(void *arg){


	int sig_received;
	sigset_t sigmask;
	sigfillset(&sigmask);
	printf("Signal handling thread %lu starting\n", pthread_self());
	while(1){

		sigwait(&sigmask, &sig_received);
		printf("Signal handling thread %lu received signal %d\n",pthread_self(), sig_received);
		
	}
	printf("Signal handling thread %lu exiting\n",pthread_self());
	pthread_exit(NULL);

}
void *normal_thread(void *arg){

	printf("Thread %lu starting\n", pthread_self());
	pause(); /* will return when any signal is received */
	printf("Thread %lu exiting\n", pthread_self());
	
}
int main(int argc, char *argv[]){

	int i ;
	pthread_t threads[NUM_THREADS];
	sigset_t sigmask;
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGINT);
	pthread_sigmask(SIG_BLOCK,&sigmask, NULL);

	printf("Master thread Id %lu\n",pthread_self());
	pthread_create(&threads[0], NULL,sigFunc,NULL);
	printf("Created signal handler thread %lu\n",threads[0]);

	for(i = 1; i < NUM_THREADS;i++){
		pthread_create(&threads[i], NULL, normal_thread, NULL);
		printf("created thread id = %lu\n",threads[i]);
	}
	sleep(1);
	printf("sending sigint(ctrl-c)\n");
	kill(getpid(), SIGINT);
	sleep(3);
	exit(EXIT_SUCCESS);
	
}
