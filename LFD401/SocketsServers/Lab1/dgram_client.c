#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>

#define MSG_LEN 1024
#define SOCK_PATH "/tmp/mySock"

int main(void){

	struct sockaddr_un uaddr;
	int msg_len, sd;
	char message[MSG_LEN];
	
	memset(message, '\0', sizeof(message));

	uaddr.sun_family = AF_UNIX;
	strcpy(uaddr.sun_path, SOCK_PATH);

	sd = socket(PF_UNIX, SOCK_DGRAM,0);

	connect(sd, (struct sockaddr *)&uaddr, sizeof(uaddr));

	msg_len = strlen(fgets(message, MSG_LEN, stdin));
	
	write(sd, message, msg_len);

	close(sd);
	exit(EXIT_SUCCESS);


}
