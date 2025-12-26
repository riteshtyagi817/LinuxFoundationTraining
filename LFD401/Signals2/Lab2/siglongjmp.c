#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<setjmp.h>
#include<signal.h>

#define ErrMsg(msg) {perror(msg); exit(errno);}

sigjmp_buf env;
int savesigs  = 1;
/* Our Signal Handler */

void sig_int(int what){

	static int val = 0;
	val++;
	printf("We have received SIGINT: val = %d\n",val);
	siglongjmp(env, val);
}
int main(int argc, char *argv[]){

	int rc;
	struct sigaction act;
	memset(&act, '\0', sizeof(act));

	/* Install signal handlers */

	act.sa_handler = sig_int;
	if(sigaction(SIGINT, &act, NULL) < 0)
		ErrMsg("sigaction")
	
	printf("Successfully installed signal handler for SIGINT\n");

	rc = sigsetjmp(env, savesigs);
	if(rc == 4){
			printf(" I am returning after 4 calls\n");
			exit(EXIT_SUCCESS);		
	}
	for(;;){

		printf("Going to wait for the signal with pause()\n");
		pause();
		printf("I rejoined inside the sleep loop\n");
		
	}
	exit(EXIT_FAILURE);
}

