#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<arpa/inet.h>
#include<errno.h>
#define MSG_LEN 1024
#define PORT_NUMBER 7177
int main(void){

	struct sockaddr_in saddr;
	int msg_len, sd;
	int yes = 1;
	int rc;
	socklen_t slen = sizeof(saddr);
	char message[MSG_LEN];
	
	memset(message, '\0', sizeof(message));

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT_NUMBER);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	sd = socket(PF_INET, SOCK_DGRAM,0);

	setsockopt(sd, SOL_SOCKET,SO_REUSEADDR, &yes,sizeof(yes));
	bind(sd, (struct sockaddr *)&saddr,sizeof(saddr));

	for(;;){
		rc = recvfrom(sd, message, sizeof(message),0,
				(struct sockaddr *)&saddr, &slen);
		if(write(STDOUT_FILENO, message, rc ) < 0)
			fprintf(stderr, "Write fail: %s\n",strerror(errno));
		/* This won't work because sd is not aware of client info */
		 //write(sd, message, rc); 
		if(sendto(sd, message, rc, 0, (struct sockaddr *)&saddr, slen) == -1)
			fprintf(stderr, "sendto fail: %s\n",strerror(errno));

		printf("Recieved the end of input\n");
	}

	exit(EXIT_SUCCESS);



}
