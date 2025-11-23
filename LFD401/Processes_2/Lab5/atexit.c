#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
void ExitFunction1(void){

	
	printf("%s should be getting called after main exits\n",__func__);
	return;
}
void ExitFunction2(void){

	printf("%s should be getting called after main exits\n",__func__);
	return;
}
int main(int argc, char *argv[]){


	int ret = 0;
	void (*fptr)(void);
	fptr = ExitFunction1;
	ret = atexit(fptr);
	if(ret)
		ErrMsg("atexit")
	printf("Exit function 1 registered\n");
	ret = atexit(ExitFunction2);
	if(ret)
		ErrMsg("atexit")
	printf("Exit function 2 registered\n");
	printf("Exit from main function\n");
	exit(EXIT_SUCCESS);

}
