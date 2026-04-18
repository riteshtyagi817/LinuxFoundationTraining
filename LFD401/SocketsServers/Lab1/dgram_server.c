#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>

#define MSG_LEN 1024

int main(void){


	struct sockaddr_un uaddr;
	int rc, sd;
	char message[MSG_LEN];
	memset(message, '\0', sizeof(message));
	// we are filling the unix domain socket details here
	uaddr.sun_family = AF_UNIX;
	strcpy(uaddr.sun_path,"/tmp/mySock");
	
	sd = socket(PF_UNIX, SOCK_DGRAM,0);

	unlink("/tmp/mySock");

	bind(sd, (struct sockaddr *)&uaddr, sizeof(uaddr));

	for(;;){
		rc = read(sd, message, sizeof(message));
		write(STDOUT_FILENO,message, rc);




	}
	close(sd);
	exit(EXIT_SUCCESS);

}
