#include<stdio.h>
#include<stdlib.h>
#include <dlfcn.h>
int main(int argc, char *argv[]){

	void *handle;
	void (*function)(void);
	handle = dlopen("./libshared.so",RTLD_LAZY);
	if(!handle){
		fprintf(stderr,"Error opening library is %s\n",dlerror());
		exit(EXIT_FAILURE);

	}
	function = dlsym(handle, "lib_function");
	function();
	dlclose(handle);
	exit(EXIT_SUCCESS);


}
