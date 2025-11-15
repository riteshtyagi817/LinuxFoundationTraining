#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/resource.h>
#define ErrMsg(msg){perror(msg);exit(errno);}
void print_rusage(int who){

	int ret = 0;
	struct rusage r_usage;
	printf("Most of the fields are currently unused in linux, we are just printing them.\n");
	ret = getrusage(who,&r_usage);
	if(ret  < 0)
		ErrMsg("getrusage")
	printf("user time used: 	%15d\n",(int)r_usage.ru_utime.tv_usec);
	printf("system time used: 	%15d\n",(int)r_usage.ru_stime.tv_usec);
	printf("maximum resident set size: %ld\n",r_usage.ru_maxrss);
	printf("integral shared memory size: %ld\n",r_usage.ru_ixrss);
	printf("integral unshared data size: %ld\n",r_usage.ru_idrss);
	printf("integral unshared stack size: %ld\n",r_usage.ru_isrss);
	printf("page reclaims: %ld\n",r_usage.ru_minflt);
	printf("page faults: %ld\n",r_usage.ru_majflt);
	printf("swaps: %ld\n",r_usage.ru_nswap);
	printf("block input operations: %ld\n",r_usage.ru_inblock);
	printf("block output operations: %ld\n",r_usage.ru_oublock);
	printf("messages sent:	%ld\n",r_usage.ru_msgsnd);
	printf("messages recieved: %ld\n",r_usage.ru_msgrcv);
	printf("signals recieved: %ld\n",r_usage.ru_nsignals);

	return;

}
int main(int argc, char *argv[]){


	int who = 0;
	who = RUSAGE_SELF;
	print_rusage(who);
	return 0;

}
