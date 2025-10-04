#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<malloc.h>
#include<errno.h>
#include<string.h>
void test1(int bytes){

	char *buf = malloc(bytes *1024);
	if(buf == NULL){

		perror("malloc");
		exit(errno);
	}
	strcpy(buf, "Testing something");
	return;

}
int main(int argc, char *argv[]){

	int bytes = 1024;
	printf("Usage: argv[1]*1024 would be allocated\n");
	if(argc > 1) bytes = atoi(argv[1]);
	malloc_stats();
	test1(bytes);
	malloc_stats();
	printf("Now we will use the usage of mallopt\n");
	printf("4096 is the threshold after which mmap will be triggered  if it cannot be served by data seg\n");

	int ret = mallopt(M_MMAP_THRESHOLD,4096);
	if(!ret){
		perror("mallopt");
		exit(errno);
	}
	test1(bytes);
	malloc_stats();
	printf("Now we can disable the usage of mmap as well for serving large requests\n");
	ret = mallopt(M_MMAP_MAX,0);
	if(!ret){
		perror("mallopt");
		exit(errno);

	}
	test1(bytes);
	malloc_stats();

	exit(EXIT_SUCCESS);
}
