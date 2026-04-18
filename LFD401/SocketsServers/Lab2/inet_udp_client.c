#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<netdb.h>
#define MSG_LEN 1024
#define PORT_NUMBER 7177
void get_addr_struct(const char *host, struct sockaddr_in *addr){

	int rc;
	struct addrinfo *res;
	rc = getaddrinfo(host, NULL, NULL, &res);

	if(rc != 0)
	{
		gai_strerror(rc);
		exit(EXIT_FAILURE);

	}
	memcpy(addr, res->ai_addr,sizeof(struct sockaddr_in));
	freeaddrinfo(res);

}
int main(int argc, char *argv[]){

	int sd, msg_len;
	char message[MSG_LEN];
	struct sockaddr_in addr;

	sd = socket(PF_INET, SOCK_DGRAM,0);

	get_addr_struct(argv[1],&addr);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_NUMBER);

	connect(sd, (struct sockaddr *)&addr, sizeof(addr));
	
	msg_len = strlen(fgets(message, MSG_LEN, stdin));
	write(sd, message, msg_len);

	memset(message, '\0', sizeof(message));

	msg_len = read(sd, message, MSG_LEN);
	write(STDOUT_FILENO, message, msg_len);

	close(sd);

	exit(EXIT_SUCCESS);

}
