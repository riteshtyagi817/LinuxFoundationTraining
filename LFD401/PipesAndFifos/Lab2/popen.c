#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
#define DEFAULT_DIR "/usr/bin"
int main(int argc, char *argv[]){

	pid_t pid;
	int pipeFd[2];
	int ret = 0;
	FILE *fp = NULL;
	char *cmd = calloc(20,sizeof(char));

	int BFSIZE = getpagesize();
	char *buffer = malloc(BFSIZE);
	if(!buffer)
		ErrMsg("malloc")
	
	char *dirName = NULL;
	if(argc > 1)
		dirName = argv[1];
	else dirName = DEFAULT_DIR;
	
	ret = pipe(pipeFd);
	if(ret)
		ErrMsg("pipe")
	strcat(cmd, "ls -l ");
	strcat(cmd, dirName);
	fflush(stdout);
	pid  = fork();
	if(0 == pid){
		printf("I am a child with process id: %d\n",getpid());
		close(pipeFd[0]);
		fp = popen(cmd,"w");
		memset(buffer,'\0',sizeof(buffer));
		strcpy(buffer, "Testing write mode in child\n");
		ret = fwrite(buffer, 1, strlen(buffer)+1, fp);
		if(ret <= 0)
			ErrMsg("fwrite")
		pclose(fp);
		exit(EXIT_SUCCESS);

	}else if(pid > 0){
		int status = 0;
		printf("I am a parent with process id: %d\n",getpid());
		close(pipeFd[1]);
		wait(&status);
		printf("Now parent is reading\n");
		fp = popen(cmd, "r");
		memset(buffer,'\0',sizeof(buffer));
		while((ret = fread(buffer, 1, BFSIZE, fp)) > 0)
			write(STDOUT_FILENO,buffer,ret);
		
		pclose(fp);
		exit(EXIT_SUCCESS);
	}
	ErrMsg("fork")
}
