#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#define DEFAULT_FILE_NAME "./test.txt"
#define BYTES_PER_LINE 15

int main(int argc, char *argv[]){

	char *fileName = NULL;
	long  file_offset = 0;
	char buf_to_read[BYTES_PER_LINE];
	memset(buf_to_read,'\0',sizeof(buf_to_read));
	int bytes_read = 0;
	if(argc > 2){

		fileName = argv[1];
		file_offset = atoi(argv[2]);
	}else if(argc > 1){
		fileName = argv[1];
	}else{
		fileName = DEFAULT_FILE_NAME;
		fprintf(stderr, "Format: executable fileName offset\n");

	}
	FILE *file = fopen(fileName, "r");
	if(!file){
		fprintf(stderr, "Fopen error\n");
		perror("fopen");
		exit(errno);
	}
	fseek(file,file_offset,SEEK_SET);
	#if 0
	do{
		bytes_read = fread(buf_to_read,1, sizeof(buf_to_read), file);
		if(bytes_read <= 0){
			if(feof(file)) break;
			else {
				if(ferror(file)){
					if(errno == EINTR) continue;
					else {
						perror("fread");
						exit(errno);
					}
				}

			}
			
		}
		for(size_t i = 0;  i < bytes_read;i++){
			fprintf(stdout, "%2.2x ",buf_to_read[i]);
		}
		fprintf(stdout,"\n");

	}while(bytes_read > 0);
	#endif
	// one other shorter way to do the above
	int i = 0;
	char c;
	while(!feof(file)){
		i++;
		if(fread(&c,1,1,file) < 0){
			perror("fread");
			exit(errno);
		}
		printf("%2.2x ",c);
		if(i % BYTES_PER_LINE == 0) printf("\n");

	}
	printf("\n");
	if(fclose(file)){
		perror("fclose");
		exit(errno);
	}
	exit(EXIT_SUCCESS);

}
