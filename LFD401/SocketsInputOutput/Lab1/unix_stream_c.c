#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>

#define MSG_LEN 1024

int main(void){



	struct sockaddr_un addr;
	int msg_len, sd;
	char message[MSG_LEN];
	
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, "tmp/mySock");

	sd = socket(PF_UNIX, SOCK_STREAM,0);

	connect(sd, (struct sockaddr *)&addr, sizeof(addr));

	msg_len = strlen(fgets(message, MSG_LEN, stdin));

	send(sd, message, msg_len, 0);

	exit(EXIT_SUCCESS);
}
