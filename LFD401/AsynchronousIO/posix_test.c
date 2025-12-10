#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<aio.h>
#include<sys/stat.h>
#include<string.h>

#define NBYTES 1024
#define NBUF 10
#define ErrMsg(msg) { perror(msg);exit(errno);}
void printbufs(char **buf, int nbytes)
{
        int j;
        fflush(stdout);
        for (j = 0; j < NBUF; j++) {
                write(STDOUT_FILENO, buf[j], nbytes);
                printf("\n");
        }
        printf("\n");
}

int main(int argc, char *argv[]){

	int fd, j,k,nbytes = NBYTES;
	char *tmp ,*buf[NBUF], *fileName = "/tmp/testfile";

	struct aiocb *cbray[NBUF], *cb;

	/* create the file and fill it with a pattern */
	if(argc > 1)
		fileName = argv[1];
	/* opening with these flags won't hurt a device node */
	fd = open(fileName, O_RDWR| O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if(fd < 0)
		ErrMsg("open")
	/* write initial data out , clear buffers, allocate aiocb's */

	for(j = 0; j < NBUF;j++){

		buf[j] = malloc(nbytes);
		sprintf(buf[j], "%4d%4d%4d%4d%4d%4d%4d%4d", j, j, j, j, j, j, j,
                        j);
		write(fd, buf[j],nbytes);
		memset(buf[j],0,nbytes);
		cb = malloc(sizeof(struct aiocb));
		cbray[j] = cb;
		memset(cb,0,sizeof(struct aiocb));
		
		cb->aio_fildes = fd;
                cb->aio_nbytes = nbytes;
                cb->aio_offset = j * nbytes;
                cb->aio_buf = (void *)buf[j];

	}
	printf("\n");

	/* (async) read the data from the file */
	printf("reading intial data from the file:\n");

	for(j = 0; j < NBUF;j++){
		cb = cbray[j];
		if(aio_read(cb)  < 0)
			printf("Error reading data from the file\n");

	}
	/* sync up and print out the reading data */
	for(j = 0; j < NBUF;j++){
		cb = cbray[j];
		while(aio_error(cb) == EINPROGRESS){
		}
		printf("%d:  aio_error=%d  aio_return=%d\n  ",
                       j, aio_error(cb), (int)aio_return(cb));

	}
        printbufs(buf, nbytes);
	  /* filling in the buffers before the write */

        for (j = 0; j < NBUF; j++) {
                tmp = buf[j];
                for (k = 0; k < nbytes; k++)
                        sprintf((tmp + k), "%1d", j);

                /*        printf ("%d, %s\n", j, buf[j]); */
        }
        printf("\n");

	  /* write the changed buffers out */

        printf(" writing new data to the file:\n");
        for (j = 0; j < NBUF; j++) {
                cb = cbray[j];
                if (aio_write(cb) < 0)
                        printf("error writing new data to file\n");
        }


        /* sync up again */

        for (j = 0; j < NBUF; j++) {
                cb = cbray[j];
                while (aio_error(cb) == EINPROGRESS) {
                }

                printf("%d:  aio_error=%d  aio_return=%d\n  ",
                       j, aio_error(cb), (int)aio_return(cb));
        }

        printbufs(buf, nbytes);

        close(fd);



	exit(EXIT_SUCCESS);

}
