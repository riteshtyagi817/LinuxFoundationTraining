#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#define DEFAULT_FILE_NAME "/etc/passwd"
#define BUF_SIZE 1024
#define ErrMsg(msg) { perror(msg);exit(errno);}
int main(int argc, char *argv[]){

	char *fileName = NULL;
	int fd = 0;
	int char_count = 0;
	ssize_t bytes_read = 0;
	ssize_t bytes_write = 0;

	char buf[BUF_SIZE];
	memset(buf, '\0',sizeof(buf));
	
	size_t file_offset = 0;
	if(argc > 1)
		fileName = argv[1];
	if(argc > 2){
		file_offset = atoi(argv[2]);
	}
	printf("File Offset is %ld\n",file_offset);
	// file is open for writing first
	fd = open(fileName, O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
	if(fd < 0)
		ErrMsg("open")
	char ch = '\0';
	printf("Enter the sentence to write to the file: ");
	int idx = 0;
	do{
		scanf("%c",&ch);
		buf[idx++] = ch;

	} while(ch != '\n');
	buf[idx] = '\0';
	printf("Current len of buf is %ld\n",strlen(buf) + 1);
	
	off_t offset = lseek(fd, 0,SEEK_CUR);
	printf("Current offset is %ld\n",offset);
	bytes_write = pwrite(fd, buf,strlen(buf) + 1, file_offset);
	if(bytes_write < 0)
		ErrMsg("pwrite")

	offset = lseek(fd, 0,SEEK_CUR);
	printf("Current offset after write  is %ld\n",offset);

	size_t bytes = 0;
	memset(buf,'\0',sizeof(buf));
	offset  = lseek(fd, 0, SEEK_CUR);
	printf("Current offset before read is %ld\n",offset);
	printf("Enter the offset and bytes you want to read from the file: ");
	scanf("%ld %lu",&offset,&bytes);
	
	bytes_read = pread(fd,buf,bytes,offset);
	if(bytes_read < 0)
		ErrMsg("pread")
	
	printf("Buffer read: %s\n",buf);
	offset  = lseek(fd, 0, SEEK_CUR);
	printf("Current offset after read is %ld\n",offset);

	close(fd);


	exit(EXIT_SUCCESS);
}
