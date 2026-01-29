#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc, char *argv[]){


	int rc;
	char *Ip;
	struct in_addr addr;
	in_addr_t addrb;

	if(argc < 2){
		printf("\nUsage: %s IP address, try again\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	Ip  = argv[1];
	printf("The original address is %s\n",Ip);
	rc = inet_aton(Ip, &addr);
	if(!rc){
		printf("inet_aton failed\n");
		exit(EXIT_FAILURE);
	}
	printf("From inet_aton: %x\n",addr.s_addr);

	addrb = inet_addr(Ip);
	printf("From inet_addr: %x\n",addrb);
	printf("The return address from inet_nota is %s\n",inet_ntoa(addr));


	exit(EXIT_SUCCESS);

}
