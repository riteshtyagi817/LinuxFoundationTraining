#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#define Error(x) perror(x); \
	exit(errno);
#define BYTES_PER_LINE 25
#define ErrMsg(msg) { perror(msg);exit(errno);}
#define DEFAULT_FILE_NAME "./test.txt"
int main(int argc, char *argv[]){

	char *fileName;
	char buffer[BYTES_PER_LINE];
	int read_bytes = 0;
	memset(buffer,'\0',sizeof(buffer));
	if(argc > 1){
		fileName = argv[1];
	}else{
		fileName = DEFAULT_FILE_NAME;
	}
	int fd = open(fileName,O_RDONLY);
	if(fd < 0)
		ErrMsg("open")
	int bytes_read = 0;
	do{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if(bytes_read < 0){

			if(errno == EINTR) 
				continue;
			else 
				ErrMsg("read")
		}
		for(size_t i = 0; i < bytes_read;i++){
			printf("%2.2x ",buffer[i]);
		}
		printf("\n");

	}while(bytes_read > 0);
	#if 0
	while(1){
		
		read_bytes = read(fd, buffer,sizeof(buffer));
		if(read_bytes < 0){
			Error("read")
		}else if(read_bytes < sizeof(buffer)) break;
		for(size_t i  = 0; i < sizeof(buffer);i++){
			//printf("%x ",buffer[i]);
			printf("%2.2x ",buffer[i]);
		}
		printf("\n");
	}
	for(size_t i = 0; i < read_bytes;i++){
		
		printf("%x ",buffer[i]);
	}
	printf("\n");
	#endif
	close(fd);

	exit(EXIT_SUCCESS);

}
