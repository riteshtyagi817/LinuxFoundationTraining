#define _GNU_SOURCE

#include<sched.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<malloc.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

int gVar = 0;
#define ErrMsg(msg) { perror(msg); exit(errno);}
int threadFunction(void *data){

	int j  = 0;
	printf("starting child thread function, pid = %d\n",getpid());
	printf("J address in the start %p\n",&j);

	for(j = 0; j < 10;j++){
		gVar = j + 1000;
		sleep(1);
		printf("Child thread running j = %d, and gVar = %d\n",j,gVar);


	}
	printf("Arg print from thread %s\n",(char *) data);
	printf("Child thread function ends\n");
	exit(EXIT_SUCCESS);
}
int main(int argc, char *argv[]){

	int j = 0, tid = 0, pageSize = 0, stackSize = 0;
	void *stack = NULL;
	int status = 0;
	printf("Starting parent with pid: %d\n",getpid());

	pageSize = getpagesize();
	stackSize = 4*pageSize;

	/* we could use malloc but this is just safer */
	// stackSize = (char *)memalign(pageSize,stackSize);
	if(posix_memalign(&stack,pageSize, stackSize))
		ErrMsg("posix_memalign")
	printf("Starting a clone thread with stack (0x%p) stackSize = %d\n",stack, stackSize);
	
	tid = clone(threadFunction, (char *) stack + stackSize,
			CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SYSVSEM | CLONE_SIGHAND
			| CLONE_THREAD, "RT writing out");
	printf("Tid : %d\n",tid);
	// we could use wait here as well
	
	wait(&status);
	
	for(j = 0; j  < 6;j++){
		gVar = j; 
		sleep(1);
		printf("Parent running with gVar= %d and j = %d\n",gVar, j);
	}
	printf("Exiting from parent\n");

	exit(EXIT_SUCCESS);
}
