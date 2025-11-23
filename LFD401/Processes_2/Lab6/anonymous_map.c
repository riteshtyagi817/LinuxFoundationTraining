#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/mman.h>
#include<sys/wait.h>
#define ErrMsg(msg){ perror(msg);exit(errno);}
int main(int argc, char *argv[]){


	int fd = -1;
	int size = getpagesize();
	int status = 0;
	char *area = NULL;
	pid_t pid = 0;
	area = mmap(NULL,size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS,fd,0);
	if(area == (void *)-1)
		ErrMsg("mmap")
	pid = fork();
	if(0 == pid){
		strcpy(area, "Message from child process.");
		printf("Child has written to %s\n",area);
		exit(EXIT_SUCCESS);

	}else if(pid > 0){
		wait(&status);
		printf("Parent has read %s\n",area);
		exit(EXIT_SUCCESS);

	}else 
		ErrMsg("fork")
	exit(EXIT_SUCCESS);
}
