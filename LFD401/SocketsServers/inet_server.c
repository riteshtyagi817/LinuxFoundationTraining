#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

#define MSG_LEN 1024

#define PORT_NUMBER 7177

int main(void){


	struct sockaddr_in addr, con_addr;
	int rc, sd, cd, yes = 1;

	socklen_t alen = sizeof(struct sockaddr_in);
	
	char message[MSG_LEN];
	
	memset(message,'\0', sizeof(message));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT_NUMBER);

	sd = socket(PF_INET, SOCK_STREAM,0);

	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

	bind(sd, (struct sockaddr *)&addr, sizeof(addr));

	listen(sd, 5);
	for(;;){
		printf("Accepting input on port %d\n",PORT_NUMBER);
		cd = accept(sd, (struct sockaddr *)&con_addr, &alen);
		rc = read(cd, message, sizeof(message));
		write(STDOUT_FILENO, message, rc);
		write(cd, message, rc);
		printf("Recieved the end of the input\n\n");
		close(cd);


	}
	close(sd);
	exit(EXIT_SUCCESS);


}
