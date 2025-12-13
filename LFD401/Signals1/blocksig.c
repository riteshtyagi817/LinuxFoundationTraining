#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
int main(int argc, char *argv[]){

	int rc  = 0;
	sigset_t sigsus, oldset;
	/* block all possible signals */

	rc  = sigfillset(&sigsus);
	rc = sigprocmask(SIG_SETMASK, &sigsus, &oldset);

	printf("going to sleep 5 seconds , try control-C!\n");
	sleep(5);
	printf("Going ahead\n");

	/* restore original mask */
	rc = sigprocmask(SIG_SETMASK, &oldset, NULL);

	/* The program should terminate before the next loop if you sent a ctrl-C while
	   the signals were blocked */
	
	/* Do something pointless forever */
	for(;;){
		printf("This is a pointless message.\n");
		sleep(1);
	}
	exit(EXIT_SUCCESS);
}
