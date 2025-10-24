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
	printf("%8o	",info.st_mode);
	printf("%4d	",info.st_uid);
	printf("%4d	",info.st_gid);
	printf("%16ld: ",info.st_size);
	printf("%s\n",fName);
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
	int ret = 0;
	printf("++++++++++++++++ Displaying info ++++++++++++++++++++\n\n");
	printf("\n\n  Mode		UID	GID		    SIZE\n\n"); 
	while((entry = readdir(dirPtr))){
		printAdditionalInfo(entry->d_name);
		ret = write(STDOUT_FILENO,"\n\n",2);
		if(ret < 0)
			ErrMsg("write")
		
	}
	closedir(dirPtr);

	exit(EXIT_SUCCESS);
}

