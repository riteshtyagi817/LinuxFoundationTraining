#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<dirent.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>

#define DEFAULT_DIR "."

#define ErrMsg(msg) { perror(msg);exit(errno);}
void processDir(char *dirName);
int main(int argc, char *argv[]){

	char *dirName = NULL;
	if(argc > 1)
		dirName = argv[1];
	else dirName = DEFAULT_DIR;
	printf("Directory %s and pid: %d\n",dirName, getpid());
	processDir(dirName);
	exit(EXIT_SUCCESS);

}
void processDir(char *dirName){
	DIR *dirPtr = NULL;
	struct dirent *dirEntry = NULL;
	struct stat info_entry;
	int status = 0;

	if(chdir(dirName))
		ErrMsg("chdir")
	
	dirPtr = opendir("./");
	if(!dirPtr)
		ErrMsg("opendir")
	
	while((dirEntry = readdir(dirPtr))){
		if(lstat(dirEntry->d_name,&info_entry))
			fprintf(stderr, "Error using lstat() with %s\n",dirEntry->d_name);
		printf("Dir name:  %s and pid: %d\n",dirEntry->d_name, getpid());
	}
	// need to reset dirPtr again
	rewinddir(dirPtr);
	
	while((dirEntry = readdir(dirPtr))){
		
		if(lstat(dirEntry->d_name, &info_entry))
			fprintf(stderr, "Error during lstat %s\n",dirEntry->d_name);
		else if(S_ISDIR(info_entry.st_mode)){
			
			pid_t pid;

			if(strcmp(dirEntry->d_name,".") &&
			   strcmp(dirEntry->d_name,"..")){
				
				fflush(stdout);
				pid = fork();
				if(0 == pid){
					printf("Pid: %d and Dir Name: %s\n",getpid(), dirEntry->d_name);
					processDir(dirEntry->d_name);
					exit(EXIT_SUCCESS);

				}else if(pid > 0){
					pid = wait(&status);
					//printf("Parent waited for child id %d\n with status %d\n",pid, status);

				}else 
					ErrMsg("fork")


			}

		}



	}
	closedir(dirPtr);





	return;
}
