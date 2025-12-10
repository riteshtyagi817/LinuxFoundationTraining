#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void ouch(int sig){

	printf("OUCH! - I got a signal %d\n",sig);
	signal(sig, SIG_DFL);
	return;

}
int main(void){


	signal(SIGINT,ouch);
	while(1){

		printf("Hello World\n");
		sleep(1);
	}
	exit(EXIT_SUCCESS);
}
