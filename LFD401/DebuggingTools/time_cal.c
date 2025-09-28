#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/time.h>
#define GET_ELAPSED_TIME(tv1,tv2) \
	((double)(tv2.tv_sec - tv1.tv_sec) + 0.000001*(tv2.tv_usec - tv1.tv_usec))

int main(int argc, char *argv[]){

	struct timeval tv1, tv2;
	int ret  = 0;
	ret = gettimeofday(&tv1,NULL);
	if(ret < 0){
		perror("gettimeofday");
		exit(EXIT_FAILURE);
	}
	long long sum = 0;
	for(int i = 0; i < 100000;i++){
		sum += i;
	}
	printf("The sum is %lld\n",sum);
	ret = gettimeofday(&tv2,NULL);
	if(ret < 0){
		perror("gettimeofday");
		exit(EXIT_FAILURE);
	}
	printf("Time elapsed is %f\n",GET_ELAPSED_TIME(tv1,tv2));


	return 0;
}
