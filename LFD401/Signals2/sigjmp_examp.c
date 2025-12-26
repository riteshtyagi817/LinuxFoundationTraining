#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<setjmp.h>

#define ErrMsg(msg) { perror(msg);exit(errno);}
sigjmp_buf senv;

void sig_int(int what){

	static int counter = 0;
	printf("We have recieved SIGINT\n");
	siglongjmp(senv, ++counter);


}
int main(int argc, char *argv[]){

	int savesigs = 1;
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = sig_int;

	if(sigaction(SIGINT,&act, NULL) < 0)
		ErrMsg("sigaction")
	printf("succefully installed signal handler for SIGINT\n");
	printf("returning from setjmp/longjmp, rc = %d\n",sigsetjmp(senv,savesigs));
	/* Hit ctrl-C whie the sleep is proceeding */
	sleep(10);
	ErrMsg("returned to the wrong place\n");

	
}
