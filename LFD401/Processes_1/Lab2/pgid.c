#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
int main(int argc, char *argv[]){

	int pgid_passed = 0;
	pid_t pid = 0;
	pid = getpid();
	int ret = 0;
	printf("Process id: %d\n",pid);
	printf("process group id: %d\n",getpgid(pid));
	printf("process group id: %d\n",getpgrp());
	if(argc > 1) pgid_passed = atoi(argv[1]);
	ret = setpgid(pid, pgid_passed);
	if(ret < 0)
		ErrMsg("setpgid")
	printf("After setting pgid\n");
	printf("process group id: %d\n",getpgid(pid));

	exit(EXIT_SUCCESS);

}
