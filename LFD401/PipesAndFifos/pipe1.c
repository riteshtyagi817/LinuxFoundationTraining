#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[]){

	int rc, filep[2], length;
	char *in_data = "pdata";
	char *out_data;
	length = strlen(in_data) + 1;
	out_data = malloc(length);
	memset(out_data,'\0',length);
	if(pipe(filep) == 0){

		rc = write(filep[1], in_data,4);
		printf("Wrote %d bytes\n",rc);
		rc = read(filep[0], out_data, 4);
		printf("read %d bytes which were %s\n",rc, out_data);
		exit(EXIT_SUCCESS);

	}

	exit(EXIT_FAILURE);

}
