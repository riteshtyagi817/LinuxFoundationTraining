#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define MSG_LEN 1024

#define PORT_NUM 7177

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

	sd = socket(sd, SOCK_STREAM,0);

	get_addr_struct(argv[1], &addr);


	addr.sin_family  = AF_INET;
	addr.sin_port = htons(PORT_NUM);
	
	connect(sd, (struct sockaddr *)&addr, sizeof(addr));

	msg_len = strlen(fgets(message, MSG_LEN, stdin));

	send(sd, message, msg_len,0);
	
	memset(message,'\0',sizeof(message));

	msg_len = recv(sd, message, MSG_LEN,0);
	
	write(STDOUT_FILENO, message, msg_len);
	
	close(sd);	

	exit(EXIT_SUCCESS);

}
