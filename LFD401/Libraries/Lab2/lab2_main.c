#include<stdio.h>
#include <dlfcn.h>
#include<stdlib.h>
#include<unistd.h>
#define LIB_NAME "./libhello_dl.so"
int main(int argc, char *argv[]){

	void *handle = NULL;
	void (*fptr)(void);

	handle = dlopen(LIB_NAME, RTLD_LAZY);
	if(!handle){

		perror("dlopen");
		fprintf(stderr,"Error opening library is %s\n",dlerror());
		exit(EXIT_FAILURE);
	}
	printf("dlopen returned\n");
	fptr = dlsym(handle, "printHello");
	if(!fptr){
		perror("dlsym");
		fprintf(stderr, "Error during dlsym is %s\n",dlerror());
		exit(EXIT_FAILURE);
	}
	fptr();
	int ret = dlclose(handle);
	printf("dlclose returned\n");
	if(ret){
		perror("dlclose");
		fprintf(stderr, "Error during dlclose is %s\n",dlerror());
		exit(EXIT_FAILURE);
	}


	return 0;
}
