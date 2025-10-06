#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<errno.h>
int main(int argc, char *argv[]){


	int count = 10;
	int ret = 0;
	char *testPtr;
	if(argc > 1){

		count = atoi(argv[1]);
	}
	for(int i = 0; i < count;i++){
		testPtr = malloc(1024);
		if(!testPtr){
			perror("malloc");
			exit(errno);
		}
	}


	exit(EXIT_SUCCESS);

}
