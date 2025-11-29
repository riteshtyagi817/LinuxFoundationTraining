#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>
#define SIZE 1024
#define ErrMsg(msg) { perror(msg);exit(errno);}

int main(int argc, char *argv[]){


	int rc, status, filedes[2];
	pid_t pid;
	char buffer[SIZE];
	if(pipe(filedes) != 0)
		ErrMsg("pipe")
	memset(buffer,0,SIZE);
	
	pid = fork();	
	if(pid > 0){
		memset(buffer,'X',SIZE);
		close(filedes[0]);
		rc = write(filedes[1], buffer, SIZE);
		printf("parent wrote %d bytes\n",rc);
		(void)wait(&status);
		printf("Parent now exiting\n");
		exit(EXIT_SUCCESS);

	}else if(0 == pid){
		close(filedes[1]);
		rc  = read(filedes[0], buffer, SIZE);
		printf("Child read %d bytes\n",rc);
		write(STDOUT_FILENO,buffer, SIZE);
		exit(EXIT_SUCCESS);

	}
	printf("fork failed\n");
	exit(EXIT_FAILURE);
}
