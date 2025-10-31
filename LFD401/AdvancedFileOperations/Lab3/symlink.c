#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
#define DEFAULT_DIR "/usr/bin/"
#define MAX_LIMIT 256
int main(int argc, char *argv[]){

	char *dir_name = NULL;
	
	DIR *dirPtr = NULL;
	struct stat fileInfo;
	memset(&fileInfo,'\0',sizeof(fileInfo));
	int ret = 0;
	char fileName[MAX_LIMIT];
	memset(fileName, '\0', sizeof(fileName));
	char fileName2[MAX_LIMIT];
	memset(fileName2, '\0', sizeof(fileName2));
	
	struct dirent *d_entry = NULL;
	if(argc > 1)
		dir_name = argv[1];
	else dir_name = DEFAULT_DIR;

	dirPtr = opendir(dir_name);
	if(!dirPtr)
		ErrMsg("opendir")

	do{
		d_entry = readdir(dirPtr);
		if(!d_entry) break;
		strcpy(fileName, d_entry->d_name);
		printf("name %s\n",fileName);
		ret = lstat(fileName,&fileInfo);
		if(ret < 0)
			ErrMsg("stat")
		if(S_ISLNK(fileInfo.st_mode)){
			
			printf("%s is a sym link\n",fileName);
			ret = readlink(fileName,fileName2, MAX_LIMIT);
			if(ret == -1)
				ErrMsg("readlink")

			// at this place stat can also work
			ret = lstat(fileName2,&fileInfo);
		       	if(ret < 0){

				printf("%s sym link is broken\n",fileName);
			}
			else printf("%s is a sym link to %s\n",fileName, fileName2);	

		}
		

	}while(d_entry);
	
	if(closedir(dirPtr))
		ErrMsg("closedir")


	exit(EXIT_SUCCESS);

}
