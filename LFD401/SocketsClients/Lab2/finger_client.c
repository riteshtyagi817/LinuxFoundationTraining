#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define MSG_LEN 1024
#define PORT_NUMBER 79 /* finger port, we can see /etc/services */

#define ErrMsg(msg) { perror(msg); exit(errno); }

void get_addr_struct(const char *host, struct sockaddr_in *addr){


	int rc;
	struct addrinfo *res;
	rc = getaddrinfo(host, NULL, NULL, &res);
	if(rc != 0){
		gai_strerror(rc);
		exit(EXIT_FAILURE);

	}
	memcpy(addr, res->ai_addr, sizeof(struct sockaddr_in));
	freeaddrinfo(res);
	return;
}
int main(int argc, char *argv[]){


	int sd, msg_len;
	char message[MSG_LEN];
	struct sockaddr_in addr;
	memset(message, 0, sizeof(message));

	/* parse the input arguements */

	if(argc <= 1){
		
		printf("Usage: %s hostname <user1 user2 ..> \n",argv[0]);
		exit(EXIT_FAILURE);
	}
	if(argc == 2){
		strcpy(message, "\n");
	}else{
		int i;
		for(i = 2; i < argc;i++){
			strcat(message, argv[i]);
			strcat(message, " ");
		}
		strcat(message, "\n");

	}
	get_addr_struct(argv[1], &addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_NUMBER);
	
	/* open the socket  and then connect */
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if(sd < 0)
		ErrMsg("Can't open a socket.\n")
	if(connect(sd, (struct sockaddr *)(&addr), sizeof(addr)))
		ErrMsg("Can't connect to a host\n")
	
	printf("Successfully connected to: %s\n",argv[1]);

	/* send the command */

	if(write(sd, message, strlen(message) < 0))
			ErrMsg("Write error\n");
	
	/* clear the message and read back the response */

	memset(message, 0, sizeof(message));
	msg_len = read(sd, message, MSG_LEN);
	
	if(msg_len < 0)
		ErrMsg("Failed reading from the socket\n")
	
	write(STDOUT_FILENO, message, msg_len);

	close(sd);

	exit(EXIT_SUCCESS);
}

