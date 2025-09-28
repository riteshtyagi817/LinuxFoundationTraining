#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){

	int *i;
	i = 0;
	printf("Ok, 2 sec pause here then I will crash\n");
	sleep(2);
	printf("The value of i is %d\n",*i);
	printf("This one should not print and I should be crashed before this\n");
	exit(EXIT_SUCCESS);
	return 0;
}
