#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
struct flock lock;
#define DEFAULT_FILE_NAME "./test.txt"
int main(int argc, char *argv[]){


	int fd = 0;
	pid_t pid;
	int flags = 0;
	int rc =  0;
	char *fileName = NULL;
	char *mode = NULL;
	int command = 0;
	flags = O_RDWR;
	pid = getpid();
	lock.l_type = F_RDLCK;
	if(argc < 3){
		printf("Usage: %s filename [r/w]\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	fileName = argv[1];
	mode = argv[2];

	fd = open(fileName, flags);
	if(fd < 0)
		ErrMsg("open")
	
	printf("PID = %d,opening = %s, with fd = %d\n",pid,fileName, fd);
	command = F_GETLK;
	rc = fcntl(fd,command,&lock);
	if(rc < 0)
		ErrMsg("fcntl")

	printf("l_type = %d, l_whence = %d, l_start = %ld, l_len = %ld, l_pid = %d\n",lock.l_type, lock.l_whence,
			lock.l_start, lock.l_len,lock.l_pid);

	command = F_SETLK;
	if(!strncmp(mode,"r",1)){
		lock.l_type = F_RDLCK;
		printf("%d doing F_RDLCK\n",pid);

	}else if(!strncmp(mode,"w",1)){
		lock.l_type = F_WRLCK;
		printf("%d doing F_WRLCK\n",pid);
	}
	rc = fcntl(fd, command,&lock);
	if(rc < 0)
		ErrMsg("fcnt")
	
	printf("l_type = %d, l_whence = %d, l_start = %ld, l_len = %ld, l_pid = %d\n",lock.l_type, lock.l_whence,
			lock.l_start, lock.l_len,lock.l_pid);
	printf("Sleeping for 10 seconds\n");
	sleep(10);
	exit(EXIT_SUCCESS);
}
