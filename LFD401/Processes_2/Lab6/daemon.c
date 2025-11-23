#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

#define ErrMsg(msg){ perror(msg); exit(errno);}
int main(int argc, char *argv[]){

	pid_t pid; 
	pid = fork();
	if(0 == pid){
		printf("I am child process with pid %d\n",getpid());
		printf("Making this process as a daemon\n");
		pause();
	}else if(pid > 0){
		printf("Parent process exits\n");
		exit(EXIT_SUCCESS);

	}else
		ErrMsg("fork")
	
	
	exit(EXIT_SUCCESS);
}
