#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/uio.h>
#define DEFAULT_FILE_NAME "./junkFile"
#define BUFLEN 1024
#define ErrMsg(msg) { perror(msg);exit(errno);}
#define NVEC 3
int main(int argc, char *argv[]){

	int fd;
	struct iovec iov[NVEC];
	char *fileName = NULL;
	char *buf = NULL;
	int j = 0;
	if(argc > 1)
		fileName = argv[1];
	else fileName = DEFAULT_FILE_NAME;
	fd = open(fileName,O_RDWR|O_CREAT|O_TRUNC,0666);
	if(fd < 0)
		ErrMsg("open");
	
	// writing the buffer to the file
	for(j = 0; j < NVEC;j++){
		buf = malloc(BUFLEN);
		if(!buf)
			ErrMsg("malloc")
		memset(buf, 'a' + j, BUFLEN);
		iov[j].iov_base = buf;
		iov[j].iov_len = BUFLEN;
	}
	ssize_t bytes_written = writev(fd, iov,NVEC);
	if(bytes_written < 0)
		ErrMsg("writev");
	
	for(j = 0; j < NVEC;j++){
			
		memset(iov[j].iov_base,'\0',BUFLEN);	
		#if 0
		char *buf = iov[j].iov_base;
	        memset(buf,'\0',BUFLEN);
		#endif	
	}
	// important part to reset the file to start
	off_t offset = 0;
	offset = lseek(fd,0,SEEK_SET);
	if(offset < 0)
		ErrMsg("lseek")

	ssize_t bytes_read = readv(fd,iov,NVEC);
	if(bytes_read < 0)
		ErrMsg("readv")
	
	for(j = 0; j < NVEC;j++)
	{
		// this won't work here
		#if 0
		for(int i = 0; i < iov[j].iov_len;i++)
			printf("%c",*(char *)(iov[j].iov_base+i));	
		#endif
		write(STDOUT_FILENO,iov[j].iov_base,BUFLEN);
		write(STDOUT_FILENO,"\n\n",2);
		free(iov[j].iov_base);

	}

	close(fd);	


	exit(EXIT_SUCCESS);

}
