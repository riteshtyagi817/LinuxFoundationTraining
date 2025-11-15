#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/resource.h>
#include<errno.h>
#include<unistd.h>
#define ErrMsg(msg) { perror(msg); exit(errno);}
//typedef struct rlimit rlimit;
void printLim(int limit, char *str,struct rlimit *rlim){

	printf("\n");
	int ret = 0;
	ret = getrlimit(limit,rlim);
	if(ret < 0)
		ErrMsg("getrlimit")
	printf("Resource %s:\n",str);
      	printf("Default current limit: %lu\n",rlim->rlim_cur);
      	printf("Default max limit: %lu\n",rlim->rlim_max);
	return;


}
void setLimit(struct rlimit *rlim,int limit){

	int ret = 0;
	ret = setrlimit(limit,rlim);
	if(ret < 0)
		ErrMsg("setrlimit")

	return;


}

int main(int agrc, char *argv[]){
	
	int sum = 0;
	printf("Printing limit details for pid:%d\n",getpid());
	struct rlimit rlim;
	printLim(RLIMIT_CPU,"RLIMIT_CPU",&rlim);
	printLim(RLIMIT_FSIZE,"RLIMIT_FSIZE",&rlim);
	printLim(RLIMIT_DATA,"RLIMIT_DATA",&rlim);
	printLim(RLIMIT_STACK,"RLIMIT_STACK",&rlim);
	printLim(RLIMIT_CORE,"RLIMIT_CORE",&rlim);
	printLim(RLIMIT_RSS,"RLIMIT_RSS",&rlim);
	printLim(RLIMIT_NPROC,"RLIMIT_NPROC",&rlim);
	printLim(RLIMIT_NOFILE,"RLIMIT_NOFILE",&rlim);
	printLim(RLIMIT_MEMLOCK,"RLIMIT_MEMLOCK",&rlim);
	printLim(RLIMIT_AS,"RLIMIT_AS",&rlim);
	printLim(RLIMIT_LOCKS,"RLIMIT_LOCKS",&rlim);
	printLim(RLIMIT_SIGPENDING,"RLIMIT_SIGPENDING",&rlim);
	printLim(RLIMIT_MSGQUEUE,"RLIMIT_MSGQUEUE",&rlim);
	printLim(RLIMIT_NICE,"RLIMIT_NICE",&rlim);
	printLim(RLIMIT_RTPRIO,"RLIMIT_RTPRIO",&rlim);

	rlim.rlim_cur = 8*1024*1024;
	rlim.rlim_max = RLIM_INFINITY;
	setLimit(&rlim,RLIMIT_CORE);
	printLim(RLIMIT_CORE,"RLIMIT_CORE",&rlim);


	exit(EXIT_SUCCESS);
}
