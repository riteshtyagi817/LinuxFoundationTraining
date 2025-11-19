#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
int main(int argc, char *argv[]){

	pid_t pid;
	int status = 0;
	printf("\nThis is the parent about to fork. pid = %d\n",getpid());
	fflush(stdout);
	pid = fork();
	if(pid == 0){
		printf("I am a child and my pid is %d\n",getpid());
		sleep(2);
		exit(EXIT_SUCCESS);

	}else if(pid > 0){
		printf("I am parent and my child id is %d\n",pid);
		pid  = wait(&status);
		if(WIFEXITED(status)){
			printf("Child with pid %d exited normally with exit code %d.\n", pid,WEXITSTATUS(status));
		}else{
			printf("Child with pid %d exited abnormally.\n",pid);
		}
		printf("Wait has been completed and pid,status returned as %d , %d.\n",pid, status);
		exit(EXIT_SUCCESS);

	}else
		ErrMsg("fork")



	exit(EXIT_SUCCESS);
}
