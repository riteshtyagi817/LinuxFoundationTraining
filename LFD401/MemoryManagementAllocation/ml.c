#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/mman.h>

#define DEATH(mess){ perror(mess); exit(errno);}
int main(int argc, char *argv[]){

	char *buf;
	int length, np = 4;
	if(argc > 1)
		np = atoi(argv[1]);
	
	length = np*getpagesize();
	
	buf = malloc(length);
	if(buf == NULL)
		DEATH("mallocing");
	if(mlock(buf,length))
		DEATH("mlock");
	printf("Locking memory success, %d pages\n",np);
	/* we can do anything with locked memory at this point */

	if(munlock(buf, length))
		DEATH("munlock");
	printf("Unlocking memory success\n");
	exit(EXIT_SUCCESS);


}
