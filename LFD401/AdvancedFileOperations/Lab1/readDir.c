#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define DEFAULT_DIR "./"
#define ErrMsg(msg) { perror(msg);exit(errno);}
void printAdditionalInfo(const char *fName){

	struct stat info;
	memset(&info, '\0', sizeof(info));
	if(stat(fName, &info) < 0)
		ErrMsg("stat")
	printf("Mode: %o\n",info.st_mode);
	return;


}
int main(int argc, char *argv[]){

	char *dirName = NULL;
	if(argc > 1)
		dirName = argv[1];
	else dirName = DEFAULT_DIR;
	DIR *dirPtr = opendir(dirName);
	if(!dirPtr)
		ErrMsg("opendir")
	
	struct dirent *entry = NULL;
	while(entry = readdir(dirPtr)){
		printf("Inode: %2ld, offset: %2u, Length of this d_name: %2u , name of this entry: %s\n",entry->d_ino,
				entry->d_off, entry->d_reclen, entry->d_name);
		printAdditionalInfo(entry->d_name);
		write(STDOUT_FILENO,"\n\n",2);
		
	}
	closedir(dirPtr);

	exit(EXIT_SUCCESS);
}

