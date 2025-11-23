#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
void myExitFunction(int status, void *data){

	printf("%s should be called after main exits\n",__func__);
	printf("Recieved status value %d from main\n",status);
	printf("Recieved data from main: %s\n", (char *)data);
	return;

}
int main(int argc, char *argv[]){

	int ret = 0;
	ret = on_exit(myExitFunction,(void *)"I am testing myExitFunction");
	if(ret)
		ErrMsg("on_exit")

	exit(EXIT_SUCCESS);
}
