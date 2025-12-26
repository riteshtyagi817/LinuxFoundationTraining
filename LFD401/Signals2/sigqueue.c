#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#define ErrMsg(msg) { perror(msg);exit(errno);}

/* Signal handler */

void sig_act(int sig, siginfo_t *si, void *a){


	printf("in handler pid = %d, SIGNAL = %d\n",getpid(), sig);
	printf("si_signo = \t%d\n", si->si_signo);
	printf("si_code = \t%d\n", si->si_code);
	printf("si_pid = \t%d\n", si->si_pid);
	printf("si_uid = \t%d\n", si->si_uid);
	printf("si_value = \t%d\n", si->si_value.sival_int);
	printf("si_int = \t%d\n", si->si_int);
	return;
}
int main(int argc, char *argv[]){

	struct sigaction act;
	int j;
	union sigval sv;

	memset(&act, 0, sizeof(act));
	act.sa_sigaction  = sig_act;
	act.sa_flags = SA_SIGINFO;
	if(sigaction(SIGINT, &act, NULL) < 0) 
		ErrMsg("sigaction")
	printf("pid = %d successfully installed signal handler for SIGINT\n", getpid());

	for(j = 0; j < 3;j++){
		printf("This is  a pointless message\n");
		sv.sival_int = j*100;
		printf("sigqueue returns %d\n",sigqueue(getpid(), SIGINT,sv));
		sleep(1);
	}

	exit(EXIT_SUCCESS);
}

