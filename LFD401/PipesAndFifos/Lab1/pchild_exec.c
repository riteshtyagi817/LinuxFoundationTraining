#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#define ErrMsg(msg) { perror(msg);exit(errno);}
#define DEFAULT_DIR "/usr/bin"
int main(int argc, char *argv[]){

	pid_t pid;
	int pipeFd[2];
	int ret = 0;
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
	fflush(stdout);
	pid  = fork();
	if(0 == pid){
		printf("I am a child with process id: %d\n",getpid());
		close(pipeFd[0]);	
		dup2(STDOUT_FILENO,pipeFd[1]);
		/* close(STDOUT_FILENO), dup(pipeFd[1]) is also valid. */
		execlp("ls", "ls", "-l" , dirName, (char *) NULL);
		exit(EXIT_FAILURE);

	}else if(pid > 0){
		printf("I am a parent with process id: %d\n",pid);
		close(pipeFd[1]);
		printf("Now parent is reading\n");
		while(ret = read(pipeFd[0], buffer,BFSIZE) > 0)
			write(STDOUT_FILENO,buffer, ret);
		
	}
	ErrMsg("fork")
}
