#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/wait.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#define ErrMsg(msg) {perror(msg);exit(errno);}
#define DEFAULT_DIR_NAME "."

bool checkDir(const char *fName){


	struct stat info;
	memset(&info, '\0',sizeof(info));
	if(stat(fName, &info) < 0)
		ErrMsg("stat")
	if(S_ISDIR(info.st_mode)) return true;
	else return false;


}

int main(int argc, char *argv[]){

	char *dirName = NULL;
	pid_t pid;
	struct dirent *entry = NULL;
	int ret = 0;
	int status = 0;
	
	if(argc > 1){
		dirName = argv[1];
	}else dirName = DEFAULT_DIR_NAME;

	DIR *dirPtr = opendir(dirName);
	if(!dirPtr)
		ErrMsg("opendir")
	while((entry = readdir(dirPtr))){
		if(strncmp(entry->d_name,".",1) == 0) continue;
		else if(strncmp(entry->d_name,"..",2) == 0) continue;
		if(checkDir(entry->d_name)){
			pid = fork();
			if(pid == 0){
				printf("I am child and my pid is %d\n",getpid());
				printf("Printing dir name %s\n",entry->d_name);
				exit(EXIT_SUCCESS);

			}else if(pid > 0){
				printf("I am parent and my child pid is %d\n",pid);
				pid = wait(&status);
				printf("I have waited for my child with Id %d and status returned as %d\n",pid, status);
				

			}else
				ErrMsg("fork")

		}

	}
	closedir(dirPtr);

	exit(EXIT_SUCCESS);
}
