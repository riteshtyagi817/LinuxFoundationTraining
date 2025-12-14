#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
void signal_handler(int sigNum){

	if(SIGINT == sigNum){
		printf("Recieved SIGINT(ctrl-C).\n");
		return;
	}
	return;	

}
int main(int argc, char *argv[]){



	if(SIG_ERR == signal(SIGINT, signal_handler)){
		perror("signal");
		exit(EXIT_FAILURE);

	}
	while(1){
		printf("Sleeping for 1 second.\n");
		sleep(1);

	}
	exit(EXIT_SUCCESS);

}
