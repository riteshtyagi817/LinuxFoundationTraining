#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
void init_fun (void) __attribute__((constructor));
void exit_fun (void) __attribute__((destructor));

void exit_func1(void) __attribute__((destructor));
void exit_func2(void) __attribute__((destructor));
void init_fun(void){

	printf("%s function should be called before main starts\n",__func__);
	return;
}
void exit_fun(void){

	printf("%s function should be called after main ends\n",__func__);
	return;
}
void exit_func1(void){

	printf("%s should be called after main ends\n",__func__);
	return;
}
void exit_func2(void){

	printf("%s should be called after main ends\n",__func__);
	return;
}


int main(int argc, char *argv[]){


	printf("Main started with pid = %d\n",getpid());
	exit(EXIT_SUCCESS);
}
