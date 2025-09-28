#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){


	for(;;){

		printf("Ok, entering an infinite loop with 2 second sleep\n");
		sleep(2);
	}
	exit(EXIT_SUCCESS);

}
