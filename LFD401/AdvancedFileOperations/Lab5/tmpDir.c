#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#define ErrMsg(msg){ perror(msg);exit(errno);}
int main(int argc, char *argv[]){

	char template[20];
	memset(template, '\0',sizeof(template));
	strncpy(template, "TmpDirXXXXXX",12);

	char *tempDir = mkdtemp(template);
	if(!tempDir)
		ErrMsg("mkdtemp")
	printf("Dir has been created with name %s\n",tempDir);
	printf("Sleeping for 10 seconds to verify dir creation\n");
	sleep(10);

	exit(EXIT_SUCCESS);
}
