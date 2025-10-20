#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#define DEFAULT_FILE_NAME "./junkFile"
#define NPOS 4
#define BUFLEN 1024

#define ErrMsg(msg) { perror(msg); exit(errno);}
int main(int argc, char *argv[]){


	int fd = 0, j = 0;
	char *fileName = DEFAULT_FILE_NAME;
	off_t pos = 0;
	char *buffer = NULL;

	if(argc > 1)
		fileName = argv[1];
	
	buffer = malloc(BUFLEN);
	if(!buffer)
		ErrMsg("malloc")
	
	fd = open(fileName, O_RDWR|O_CREAT|O_TRUNC,0666);
	if(fd < 0)
		ErrMsg("open")
	// now we are writing to the junkfile
	
	for(j = 0; j < NPOS;j++){
		memset(buffer,'0' + j,BUFLEN);
		pos = j*BUFLEN;
		printf("writing at pos %ld\n",pos);
		pwrite(fd,buffer,BUFLEN,pos);
		pos = lseek(fd,0,SEEK_CUR);
		printf("After the %dth write the pos is %ld\n",j,pos);	

	}	
	// now we will read from the junk file
	for(j = 0; j < NPOS;j++){
		memset(buffer,'\0',BUFLEN);
		pos = j*BUFLEN;
		printf("reading at pos %ld\n",pos);
		pread(fd,buffer, BUFLEN,pos);
		printf("%s\n",buffer);
		pos = lseek(fd,0,SEEK_CUR);
		printf("After the %dth read the pos is %ld\n",j,pos);
	}
	


	
	free(buffer);
	close(fd);

	exit(EXIT_SUCCESS);
}
