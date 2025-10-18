#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#define DEFAULT_FILE_NAME "/etc/passwd"
#define BYTES_PER_LINE 16
#define ErrMsg(msg) { perror(msg);exit(errno);}
int main(int argc, char *argv[]){

	char *fileName = NULL;
	int fd = 0;
	int char_count = 0;
	//char buf[BYTES_PER_LINE];
	char c = '\0';

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
		ErrMsg("fopen")
	printf("Enter the count of chars you want to enter: ");
	scanf("%d",&char_count);
	scanf("%c",&c); // just to clear new line
	while(char_count--){
		scanf("%c",&c);
		//if(pwrite(file,





	}



	exit(EXIT_SUCCESS);
}
