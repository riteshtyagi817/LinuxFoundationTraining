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
#define PORT_NUMBER 7
#define ErrMsg(msg) { perror(msg); exit(errno); } 

void get_addr_struct(const char *host, struct sockaddr_in *addr){
	
	int rc ;
	struct addrinfo *res;
	rc = getaddrinfo(host, NULL, NULL, &res);
	if(rc != 0){
		gai_strerror(rc);
		exit(EXIT_FAILURE);

	}
	memcpy(addr, res->ai_addr, sizeof(struct sockaddr_in));
	freeaddrinfo(res);

}
int main(int argc, char **argv){


	int sd, msg_len;
	char message[MSG_LEN];
	struct sockaddr_in addr;
	if(argc < 2){
		printf("USAGE %s host\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if(sd < 0)
		ErrMsg("can't open a socket\n");
	
	printf("Opened the socket just fine\n");
	get_addr_struct(argv[1], &addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_NUMBER);
	
	if(connect(sd, (struct sockaddr *)&addr, sizeof(addr)))
		ErrMsg("can't connect to host\n");
	
	printf("connected to the host just fine\n");
	
	printf("Type in a message to send to %s\n", argv[1]);
	
	msg_len = strlen(fgets(message, MSG_LEN, stdin));

	if(write(sd, message, msg_len) < 0)
		ErrMsg("Failed writing to the socket\n")
	
	memset(message, 0, MSG_LEN);

	printf("\n cleared the message , am going to read it back from the socket\n\n");
	
	msg_len = read(sd, message, MSG_LEN);
	
	if(msg_len < 0)
		ErrMsg("Failed reading from the socket\n");
	
	write(STDOUT_FILENO, message, msg_len);
	
	close(sd);
	exit(EXIT_SUCCESS);	

}
