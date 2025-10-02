#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/syscall.h>
int main(int argc, char *argv[]){

	pid_t pid = syscall(SYS_getpid);
	printf("My Process id is %u\n",pid);

	pid_t ppid = syscall(SYS_getppid);
	printf("My Parent Process id is %u\n",ppid);

	exit(EXIT_SUCCESS);
}
