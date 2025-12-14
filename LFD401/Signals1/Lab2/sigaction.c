#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>
#include<string.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
void sig_int(int sigNum){

	printf("We have recieved SIGINT.\n");
	printf("we will sleep for 2 seconds here\n");
	sleep(2);
	printf("Done, sleeping for 2 seconds here.\n");

}
void sig_quit(int sigNum){

	printf("We have recieved SIGQUIT.\n");
	abort();
}
int main(int argc, char *argv[]){

	struct sigaction sa;
	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = sig_int;
	if(sigaction(SIGINT, &sa, NULL) < 0) 
		ErrMsg("sigaction")
	printf("Successfully installed signal handler for SIGINT.\n");
	
	
	sa.sa_handler = sig_quit;
	if(sigaction(SIGQUIT, &sa, NULL) < 0) 
		ErrMsg("sigaction")

	printf("Successfully installed signal handler for SIGQUIT.\n");
	
	for(;;){
		printf("This is a pointless message.\n");
		sleep(1);
	}
	exit(EXIT_SUCCESS);

}
