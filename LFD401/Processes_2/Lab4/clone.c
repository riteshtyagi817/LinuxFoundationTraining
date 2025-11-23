#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include <sched.h>

#define ErrMsg(msg) { perror(msg);exit(errno);}
int globVar = 0;
int (*fptr)(void *arg);
int threadFunction(void *String){
	printf("Writing string in thread function %s\n",(char *)String);
	globVar = 34;
	printf("globVar in thread: %d\n",globVar);

	exit(EXIT_SUCCESS);

}
int main(int argc, char *argv[]){

	printf("globVar in parent: %d\n",globVar);
	// Thread creation using clone system call.
	fptr = threadFunction;
	int pageSize = getpagesize();
	char *stackSize = malloc(pageSize);
	if(!stackSize)
		ErrMsg("mallo")
	int ret = clone(fptr,(void *)stackSize+pageSize,CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SYSVSEM|CLONE_SIGHAND|CLONE_THREAD, "Ritesh");
	printf("Returned value from clone: %d\n",ret);
	printf("globVar in parent after clone: %d\n",globVar);



	exit(EXIT_SUCCESS);

}
