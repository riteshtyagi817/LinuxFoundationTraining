#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char *argv[]){


	FILE *fp;
	int nbytes, BSIZE = getpagesize();
	//char *buffer = malloc(BSIZE);
	char *buffer = calloc(BSIZE,sizeof(char));
	char *command = "ls -l /boot";
	
	if(argc  > 1)
		command = argv[1];
	fp = popen(command, "r");
	while((nbytes = fread(buffer, 1, BSIZE,fp)) > 0)
		fwrite(buffer,1,nbytes,fp);
	printf("EOF = %d and Error = %d\n",feof(fp), ferror(fp));
	printf("Buffer read %s\n",buffer);
	pclose(fp);
	exit(EXIT_SUCCESS);


}
