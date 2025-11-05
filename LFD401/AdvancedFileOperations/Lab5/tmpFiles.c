#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}

int main(int argc, char *argv[]){

	int fd = 0;
	int bytes_write = 0;
	int bytes_read = 0;
	char buf[18];
	char template[20];
	memset(template,'\0',sizeof(template));
	strncpy(template, "TryOutXXXXXX",12);
	memset(buf, '\0',sizeof(buf));
	fd = mkstemp(template);
	if(fd < 0)
		ErrMsg("mkstemp")
	printf("File has been created now sleeping for 20 seconds to verify.\n");
	sleep(20);

	bytes_write = write(fd,"Testing Something",17);
	if(bytes_write < 17)
		ErrMsg("write")
	lseek(fd,0,SEEK_SET);
	bytes_read = read(fd, buf, 17);
	if(bytes_read < 17)
		ErrMsg("read")
	bytes_write = write(STDOUT_FILENO,buf,17);
	if(bytes_write < 17)
		ErrMsg("write")
	close(fd);


	exit(EXIT_FAILURE);

}
