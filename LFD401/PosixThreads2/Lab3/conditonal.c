#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

#define NUM_WORKERS 3

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
/* Both the counter and the "exiting" flag are protected by the lock */

static volatile int counter = 0;
static volatile int exiting  = 0;

/*  Wait for some data to show up in the counter , then "process" the data.
 *  To process the data just decrement the counter and sleep for one second */

void * decrementer(void *arg){

	int counterVal;
	for(;;){
		
		/* Lock the mutex so we can safely examine the counter and the "exiting" flag */
		pthread_mutex_lock(&lock);
		while(!exiting && (counter <= 0)){
			/* "cond" should be signalled when the counter is incremented or the "exiting"
			 * flag is set , so we will wake up as soon as we have something to do */
			pthread_cond_wait(&cond, &lock);

		}
		if(exiting){
			pthread_mutex_unlock(&lock);
			pthread_exit(NULL);
		}
		/* We copy "counter" into the local variable so that we can print it even after unlock */
		counterVal = --counter;
		pthread_mutex_unlock(&lock);

		printf("Thread %ld decrementing to %d\n", pthread_self(), counterVal);
		sleep(1);

	}
	return NULL;

}
int main(int argc, char *argv[]){


	pthread_t threads[NUM_WORKERS];
	int i, val;
	/* threads creation */
	for(i  = 0; i < NUM_WORKERS;++i)
		pthread_create(&threads[i], NULL, decrementer, NULL);

	for(;;){

		switch(scanf("%d",&val)){

			case 1:
				/* we got a value to add to the counter. Add it then broadcast 
				 * the cond to wake up any threads waiting for something to do */
				pthread_mutex_lock(&lock);
				counter += val;
				pthread_cond_broadcast(&cond);
				pthread_mutex_unlock(&lock);
				break;
			case EOF:
				/* we got an EOF, need to exit all the threads by using "exiting" flag
				 * then wait for them to exit cleanly before we close the application */
			       	pthread_mutex_lock(&lock);
		       	       	exiting = 1;
				pthread_cond_broadcast(&cond);
			 	pthread_mutex_unlock(&lock);
				for(i = 0; i < NUM_WORKERS;i++)
					pthread_join(threads[i], NULL);
				exit(EXIT_SUCCESS);
			default:
				fprintf(stderr, "You must enter the numbers or EOF to end the program.\n");
				exit(EXIT_FAILURE);	
		
		}



	}

	exit(EXIT_SUCCESS);

}
