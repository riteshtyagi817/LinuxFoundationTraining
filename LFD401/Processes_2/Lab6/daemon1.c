#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

#define ErrMsg(msg){ perror(msg); exit(errno);}
int main(int argc, char *argv[]){

	printf("Making this process daemon and pausing\n");
	if(daemon(0,1))
		ErrMsg("daemon")
	printf("Now it has become daemon, pausing it\n");
	pause();		
	exit(EXIT_SUCCESS);
}
