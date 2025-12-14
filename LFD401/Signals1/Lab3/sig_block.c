#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<signal.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
void sig_int(int sig_num){

	printf("We have recieved SIGINT.\n");
	printf("Sleeping for 5 seconds.\n");
	sleep(5);
	printf("Sleeping done.\n");
	return;
}
void sig_quit(int sig_num){
	
	printf("We have recieved SIGQUIT.\n");
	abort();
}	
int main(int argc, char *argv[]){

	int rc = 0;
	struct sigaction sa_int, sa_quit;
	sigset_t sa_mask;
	
	memset(&sa_int, '\0', sizeof(sa_int));
	memset(&sa_quit, '\0', sizeof(sa_quit));

	//blocking SIQUIT while executing sigint
	
	rc = sigemptyset(&sa_mask);
	printf("rc = %d from sigemptyset.\n",rc);

	rc = sigaddset(&sa_mask, SIGQUIT);
	printf("rc = %d from siaddset.\n",rc);

	sa_int.sa_handler = sig_int;
	sa_int.sa_mask = sa_mask;
	if(sigaction(SIGINT,&sa_int, NULL) < 0)
		ErrMsg("sigaction")
	printf("Successfully installed SIGINT\n");

	sa_quit.sa_handler = sig_quit;

	if(sigaction(SIGQUIT, &sa_quit, NULL) < 0)
		ErrMsg("sigaction")
	
	printf("Successfully installed SIGQUIT\n");

	for(;;){
		printf("This is a pointless message.\n");
		sleep(1);

	}
	exit(EXIT_SUCCESS);

}

