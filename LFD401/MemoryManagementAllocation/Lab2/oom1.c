#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MB (1024*1024)

int main(int argc, char *argv){


	int j;
	char *buf;
	for(j = 0;;j++){
		buf = malloc(MB);
		memset(buf,j,MB);

	}


	exit(EXIT_SUCCESS);

}
