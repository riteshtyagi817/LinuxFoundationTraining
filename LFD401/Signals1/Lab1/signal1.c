#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>


void sig_int(int sigNum){

	printf("We have recieved SIGINT, continuing\n");
}
void sig_quit(int sigNum){

	printf("We have recieved SIGQUIT, dumping core and terminating.\n");
	abort();

}
int main(int argc, char *argv[]){

	// Installing signal handlers 
	signal(SIGINT,sig_int);
	signal(SIGQUIT,sig_quit);
	while(1){
		printf("Just sleeping for 1 second\n");
		sleep(1);
	}


	exit(EXIT_SUCCESS);
}
