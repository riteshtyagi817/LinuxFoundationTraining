#include<stdio.h>
#include<stdlib.h>
#include<sys/un.h>
#include<sys/socket.h>
#include<unistd.h>


#define MSG_LEN 1024

int main(void){


	struct sockaddr_un addr;
	int msg_len, sd,cd;
	int rc  = 0;
	char message[MSG_LEN];

	addr.sun_family = AF_UNIX;

	socklen_t slen = sizeof(struct sockaddr_un);

	strcpy(addr.sun_path,"/tmp/mySock");

	sd = socket(PF_UNIX,SOCK_STREAM,0);

	unlink("/tmp/mySock");

	bind(sd, (struct sockaddr *)&addr, sizeof(addr));

	for(;;){

		cd = accept(sd, NULL, &slen);
		rc = recv(cd, message, sizeof(message), 0);

		write(STDOUT_FILENO, message, rc);
		close(cd);


	}
	close(sd);
	exit(EXIT_SUCCESS);
}
