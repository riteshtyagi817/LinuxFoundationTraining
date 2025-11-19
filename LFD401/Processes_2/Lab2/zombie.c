#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}

int main(int argc, char *argv[]){

	pid_t pid = 0;
	printf("This is the parent with pid %d and about to fork.\n",getpid());
	fflush(stdout);
	pid = fork();
	if(pid > 0){
		printf("I am a parent and my child pid is %d.\n",pid);
		printf("waiting for 10 seconds.\n");
		sleep(10);
		printf("I am parent and now I am exiting too.\n");
		exit(EXIT_SUCCESS);

	}else if(pid == 0){
		printf(" I am a child and my pid is %d\n",getpid());
	        printf(" I am exiting quicky to become zombie for some time as my parent didn't wait for me.\n");
		exit(EXIT_SUCCESS);	
	}else
		ErrMsg("fork")

	exit(EXIT_SUCCESS);

}
