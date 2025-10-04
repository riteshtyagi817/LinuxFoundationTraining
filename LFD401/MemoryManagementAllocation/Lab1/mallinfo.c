#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<malloc.h>
#include<string.h>
int main(int argc, char *argv[]){


	int bytes = 1024;
	if(argc > 1) bytes = atoi(argv[1]);
	printf("Usage of mallinfo first \n");

	struct mallinfo2 mlt;
	memset(&mlt, '\0',sizeof(mallinfo2));
	mlt  = mallinfo2();
	printf("No of mapped regions is %ld\n",mlt.hblks);
	printf("Total allocated space is %ld\n",mlt.uordblks);
	printf("Total free space is %ld\n",mlt.fordblks);

	char *buf = malloc(bytes*1024);
	if(buf == NULL){
		perror("malloc");
		exit(errno);
	}

	printf("No of mapped regions is %ld\n",mlt.hblks);
	printf("Total allocated space is %ld\n",mlt.uordblks);
	printf("Total free space is %ld\n",mlt.fordblks);
	
	exit(EXIT_SUCCESS);
}
