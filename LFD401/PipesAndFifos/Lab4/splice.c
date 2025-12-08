#define _GNU_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}

int main(int argc, char *argv[]){

	char inFile[128] = "./infile";
	char outPipe[128] = "./outPipe";
	/* 1st arg - input file name, default = ./infile */
	/* 2nd arg - outpipename , default = ./outPipe */
	/* 3rd arg - size of chunk , default = infinite by default */

	int rc, in_fd,out_fd, numBuf = INT_MAX;

	if(argc > 1)
		strcpy(inFile, argv[1]);
	if(argc > 2)
		strcpy(outPipe,argv[2]);
	if(argc > 3)
		numBuf = atoi(argv[3]);

	printf("Input file: %s, Output pipe: %s\n",inFile, outPipe);
	fflush(NULL);
	
	in_fd = open(inFile , O_RDONLY);
	if(in_fd < 0)
		ErrMsg("open")
	
	out_fd = open(outPipe, O_WRONLY);
	if(out_fd < 0)
		ErrMsg("open")
	do{
		rc = splice(in_fd, NULL, out_fd, NULL,numBuf, 0);
		if(rc < 0)
			ErrMsg("splice")
		printf("Transferred %8d bytes\n",rc);

	}while(rc > 0);
	close(in_fd);
	close(out_fd);
	
	printf("done\n");

	exit(EXIT_SUCCESS);
}

