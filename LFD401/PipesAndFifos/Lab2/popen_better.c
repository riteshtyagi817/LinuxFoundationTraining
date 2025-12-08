#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

#define ErrMsg(msg) { perror(msg);exit(errno);}
#define DEFAULT_DIR "/usr/bin" 

int main(int argc, char *argv[]){

	pid_t pid;
	char *dirName = NULL;
	if(argc > 1)
		dirName = argv[1];
	else dirName = DEFAULT_DIR;

	int ret, pipeDesc[2];
	int BUFSIZE = getpagesize();
	char *buffer = calloc(BUFSIZE,sizeof(char));

	if(-1 == pipe(pipeDesc))
		ErrMsg("pipe")
	
	printf("This is the parent just before the fork\n");
	fflush(stdout);

	pid  = fork();
	if(pid > 0){
		printf("This is the parent after the fork\n");
		close(pipeDesc[1]);
		printf(" Paren has just read below from the pipe\n");
		while((ret = read(pipeDesc[0],buffer,BUFSIZE)) > 0){
			write(STDOUT_FILENO,buffer, ret);
		}
		exit(EXIT_SUCCESS);
	}else if(0 == pid){
		FILE *fp = NULL;
		close(pipeDesc[0]);
		char cmd[1024] = "ls -l ";
		fp = popen(strcat(cmd, dirName),"r");
		while((ret = fread(buffer, 1, BUFSIZE,fp)) > 0){
			write(pipeDesc[1],buffer,ret);

		}
		pclose(fp);
		printf("This is the child , after the fork\n");
		exit(EXIT_SUCCESS);

	}
	ErrMsg("fork")

}
