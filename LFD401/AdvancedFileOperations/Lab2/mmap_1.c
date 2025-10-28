#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/mman.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
#define DEFAULT_FILE_NAME "./test.txt"

int main(int argc, char *argv[]){


	int fd, i, wb;
	char *temp = NULL;
	char *mapped_area = NULL;
	char *fileName = NULL;
	struct stat statInfo;
	off_t file_size = 0;

	char buf[2] = "RT";
	
	if(argc > 1)
		fileName = argv[1];
	else fileName = DEFAULT_FILE_NAME;

	fd = open(fileName,O_RDWR);
	if(fd < 0) 
		ErrMsg("open");

	if(fstat(fd, &statInfo))
		ErrMsg("fstat");
	
	file_size = statInfo.st_size;

	printf("Memory Mapping file: %s of size %ld bytes \n",fileName,file_size);



	mapped_area = mmap(NULL,file_size,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	
	if(mapped_area == MAP_FAILED)
		ErrMsg("mmap")


	close(fd);

	temp = mapped_area;

	for(i = 0; i < file_size -1;i += 2,temp += 2)
		memcpy(temp,&buf,2);

	wb = write(STDOUT_FILENO,mapped_area,file_size);

	if(wb != file_size)
		ErrMsg("write")
	




	exit(EXIT_SUCCESS);
}

