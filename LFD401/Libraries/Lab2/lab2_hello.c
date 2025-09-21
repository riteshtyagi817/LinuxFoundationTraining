#include<stdio.h>
void my_func(void)__attribute__((constructor));
void exit_fun(void)__attribute__((destructor));

void my_func(void){

	printf("This is the constructor function and it should be called before dlopen returns\n");
	return;

}
void exit_fun(void){

	printf("This is the destructor function and it should be called after dlclose returns\n");
	return;
}

void printHello(void){

	printf("Hello from Dynamic Library\n");
	return;
}
