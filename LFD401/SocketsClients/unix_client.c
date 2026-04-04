#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>

#define MSG_LEN 1024

int main(void){

	struct sockaddr_un uaddr;
	int msg_len, sd;
	char message[MSG_LEN];
	uaddr.sun_family = AF_UNIX;
	strcpy(uaddr.sun_path,"/tmp/mysock");
	
	sd = socket(PF_UNIX, SOCK_STREAM, 0);
	connect(sd, (struct sockaddr *)&uaddr, sizeof(uaddr));
	
	msg_len = strlen(fgets(message, MSG_LEN, stdin));
	write(sd, message, msg_len);

	close(sd);
	exit(EXIT_SUCCESS);
	
}
