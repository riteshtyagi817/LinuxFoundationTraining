#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/mman.h>

#define DEFAULT_FILE_NAME "test.txt"
#define ErrMsg(msg) { perror(msg);exit(errno);}
int main(int argc, char *argv[]){

	char *fileName = NULL;
	void *mapAddr = NULL;
	char *buf = NULL;
	char ch = '\0';
	int fd = 0;
	int ret = 0;
	size_t idx = 0;
	if(argc > 1)
		fileName = argv[1];
	else fileName = DEFAULT_FILE_NAME;

	fd = open(fileName, O_RDWR);
	if(fd < 0)
		ErrMsg("open")

	struct stat info;
	memset(&info, '\0',sizeof(info));
	if(stat(fileName,&info) < 0)
		ErrMsg("stat")
	off_t file_size = info.st_size;

	mapAddr = mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
	if(mapAddr == MAP_FAILED)
		ErrMsg("mmap")


	// first demo is from read 
	buf = malloc(file_size+1);
	if(!buf)
		ErrMsg("malloc")
	memset(buf,'\0',file_size+1);
	memcpy(buf,mapAddr,file_size);
	buf[file_size] = '\0';
	printf("File read through mmap is:\n%s",buf);


	// now we will write something in between or at the start of the file
	memset(buf,'\0',file_size+1);
	do{
		ch = getchar();
		buf[idx] = ch;
		idx++;

	}while(ch != '\n');
	
	memcpy(mapAddr,buf,idx);	

	memset(buf,'\0',file_size+1);
	memcpy(buf,mapAddr,file_size);
	buf[file_size] = '\0';
	printf("File read through mmap is:\n%s",buf);

	ret = munmap(mapAddr, file_size);
	if(ret < 0)
		ErrMsg("munmap")
	ret = close(fd);
	if(ret < 0)
		ErrMsg("close")

	exit(EXIT_SUCCESS);

}
