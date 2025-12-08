#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<fcntl.h>

#define ErrMsg(msg) { perror(msg);exit(errno);}
#define FIFO "/tmp/myFifo"
int main(int argc, char *argv[]){

	int ret = 0;
	pid_t pid;
	int fd = 0;
	char message[] = "Hello from the child\n";
	ret = mkfifo(FIFO, 0666);
	if(ret < 0)
		ErrMsg("mkfifo")
	
	fflush(stdout);
	pid = fork();
	if(0 == pid){
		
		printf("I am child with pid %d\n",getpid());
		fd  = open(FIFO,O_WRONLY);
		if(fd < 0) ErrMsg("open")
		printf("writing something into fifo\n");
		if(write(fd, message, strlen(message) + 1) < 0) ErrMsg("write")
		close(fd);
		exit(EXIT_SUCCESS);


	}else if(pid > 0){
		printf("I am a parent process with pid %d\n",getpid());
		fd = open(FIFO, O_RDONLY);
		if(fd < 0) ErrMsg("open")
		printf("reading from the fifo\n");
		if(read(fd, message, sizeof(message) < 0)) ErrMsg("read")
		printf("Message read from FIFO: %s\n",message);
		close(fd);
		unlink(FIFO);
		exit(EXIT_SUCCESS);

	}else
		ErrMsg("fork")

	exit(EXIT_SUCCESS);

}
