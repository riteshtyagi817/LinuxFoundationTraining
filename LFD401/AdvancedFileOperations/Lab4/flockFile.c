#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/file.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
#define DEFAULT_FILE_NAME "./test.txt"
#define BUF_LEN 50
int main(int argc, char *argv[]){

	printf("Usage: ./executable arg1 where arg1 implies whether lock is exclusive or shared.\n");
	int fd = 0;
	char *fileName = NULL;
	size_t bytes_read = 0;
	char buf[BUF_LEN];
	memset(buf, '\0',sizeof(buf));
	int op = 0;
	int ret = 0;
	fileName = DEFAULT_FILE_NAME;
	fd = open(fileName,O_RDWR);
	if(fd < 0)
		ErrMsg("open")
		
	if(argc == 2){
		if(strncmp(argv[1],"exclusive",9) == 0){
			printf("Lock is exclusive\n");
			op = LOCK_EX;

		}
		else{
			printf("Lock is shared\n");
		       	op  = LOCK_SH;
		}
	}
	ret = flock(fd,op);
	if(ret < 0)
		ErrMsg("flock")
	printf("Lock has been applied to the file\n");
	sleep(15);
	printf("Trying to read 49 bytes from the file.\n");
	bytes_read = read(fd, buf, 49);
	if(bytes_read < 49){
		printf("could not read 49 bytes from the file.\n");
		exit(errno);
	}
	printf("Buf read %s\n",buf);
	printf("Now unlocking the file\n");
	ret = flock(fd,LOCK_UN);
	if(ret < 0)
		ErrMsg("flock")
	ret = close(fd);
	if(ret < 0)
		ErrMsg("close")

	exit(EXIT_SUCCESS);


}
