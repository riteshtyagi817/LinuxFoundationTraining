#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<malloc.h>

void doit(void){

	char *buf;
	buf = malloc(1000);
}
int main(int argc, char *argv[]){


	int j;
	for(j = 0; j < 10;j++){
		doit();
		printf("allocated the %3d buffer\n",j);

	}
	exit(EXIT_SUCCESS);

}
