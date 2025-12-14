#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}

#define NUMSIGS 64
int sig_count[NUMSIGS+1]; 
volatile static int line;
volatile int sigNumBuf[6400];
volatile int sigCountBuf[6400];

void sig_handler(int sigNum){
	sig_count[sigNum]++;
	sigNumBuf[line] = sigNum;
	sigCountBuf[line] = sig_count[sigNum];
	line++;
}
int main(int argc, char *argv[]){

	sigset_t new_sigmask, old_sigmask;
	struct sigaction sigact, oldact;
	int sigNum, rc, i;
	// Firstly we need to block all the signals so that each one come in sequence 
	rc = sigfillset(&new_sigmask);
	printf("rc value sigfillset: %d\n",rc);
	rc = sigprocmask(SIG_SETMASK,&new_sigmask,&old_sigmask);
	printf("rc value sigprocmask: %d\n",rc);

	memset(&sigact, '\0', sizeof(sigact));
	sigact.sa_handler = sig_handler;
	// important step
	sigact.sa_mask = new_sigmask;
	sigact.sa_flags = 0; // not needed as of now
	// Now we will need to register all the signals using sigaction
	for(sigNum = 1; sigNum <= NUMSIGS;sigNum++){
		if(SIGKILL == sigNum || SIGSTOP == sigNum || 32 == sigNum || 33 == sigNum){
			printf("--");
		}else{
			sigaction(sigNum, &sigact,&oldact);
		        rc = raise(sigNum);	
		        rc = raise(sigNum);	
		        rc = raise(sigNum);	
			if(rc){
				printf("Failed on signal %d\n",sigNum);
			}else{
				printf("%4d",sigNum);

			}

		}
		if(sigNum%16 == 0) printf("\n");

	}
	fflush(stdout);
	/* restore original mask */
	rc = sigprocmask(SIG_SETMASK,&old_sigmask,NULL);
        
	printf("\n Signal Number(Times Processed)\n");
	printf("-----------------------------------\n");

	for(i = 1;  i <= NUMSIGS;i++){
		printf("%4d:%3d  ",i,sig_count[i]);
		if(i % 8 == 0)
			printf("\n");
	}


	printf("\n");

	printf("History Signal Number(count processed\n");
	printf("-------------------------------------\n");
	for(i = 0; i < line;i++){
		if(i % 8 == 0)
			printf("\n");
		printf("%4d(%1d)",sigNumBuf[i], sigCountBuf[i]);
	}	
	printf("\n");
	exit(EXIT_SUCCESS);
}
