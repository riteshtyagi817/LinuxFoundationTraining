#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<malloc.h>

#define PRINTIT(a) fprintf(stderr,"       " #a		"\t = %ld",mi->a)


void dump_mi(struct mallinfo2 *mi){

	PRINTIT(arena);
	PRINTIT(ordblks);
	PRINTIT(smblks);
	fprintf(stderr,"\n");
	PRINTIT(hblks);
	PRINTIT(hblkhd);
	PRINTIT(usmblks);
	fprintf(stderr,"\n");
	PRINTIT(fsmblks);
	PRINTIT(uordblks);
	PRINTIT(fordblks);
	PRINTIT(keepcost);


}
void doit(int bytes){


	char *buf;
	struct mallinfo2 mi;
	buf = malloc(bytes);
	// so that compiler will see that it is getting used , else compile with -O0( no optimization)
	strncpy(buf, "\n Allocating %10d bytes ---\n",bytes);
	fprintf(stderr,buf,bytes);
	malloc_stats();
	mi = mallinfo2();
	dump_mi(&mi);
	free(buf);
	return;

}

int main(int argc, char *argv[]){



	int threshold, ret;
	if(argc > 1){
		threshold = atoi(argv[1]);
		ret = mallopt(M_MMAP_THRESHOLD,threshold);
		fprintf(stderr," ret = %d from requesting mmap"
				" for more than threshold %d bytes\n",ret, threshold);


	}
	doit(13);
	doit(13*1024);
	doit(13*1024*1024);
	exit(EXIT_SUCCESS);

}
