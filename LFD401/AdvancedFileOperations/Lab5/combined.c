#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
int main(){

	int fd = 0;
	FILE *fp = NULL;
	char *f_temp = NULL;
	char template_file[] = "FILEXXXXXX";
	char template_dir[] = "DIRXXXXXX";
	printf("template file %s\n",template_file);
	printf("template dir %s\n",template_dir);
	fd = mkstemp(template_file);
	
	f_temp = mkdtemp(template_dir);

	printf("created Dir name %s\n",f_temp);

	// useful function to return file pointer for a temp file 
	fp = tmpfile();
	fprintf(fp,"Writing something\n");
	fseek(fp,0,SEEK_SET);
	// just to see the temp file functionality
	char buf[20];
	memset(buf,'\0',sizeof(buf));
	fscanf(fp,"%s", buf);
	printf("buf print %s\n",buf);
	sleep(10);

	unlink(template_file);
	rmdir(template_dir);
	fclose(fp);
	close(fd);
	exit(EXIT_SUCCESS);
}
