#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>

#define MSG_LEN 1024

int main(void){


	struct sockaddr_un uaddr;
	int rc, sd, cd;
	socklen_t alen = sizeof(struct sockaddr_un);

	char message[MSG_LEN];

	uaddr.sun_family = AF_UNIX;
	strcpy(uaddr.sun_path, "/tmp/mysock");

	sd = socket(PF_UNIX, SOCK_STREAM, 0);
	unlink("/tmp/mysock");

	bind(sd, (struct sockaddr *)&uaddr, sizeof(uaddr));

	listen(sd, 5);

	for(;;){
		cd = accept(sd,NULL, &alen);

		rc = read(cd,message,sizeof(message));
		write(STDOUT_FILENO, message, rc);
		close(cd);

	}
	close(sd);
	exit(EXIT_SUCCESS);
}
