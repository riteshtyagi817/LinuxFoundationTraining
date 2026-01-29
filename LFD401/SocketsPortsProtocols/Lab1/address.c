#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>


#define DEFAULT_HOST "localhost"
#define DEFAULT_SERVICE "http"
#define DEFAULT_PROTOCOL "tcp"

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

}
int resolve(const char *host, const char *service, const char *proto, struct sockaddr_in *addr){
	
	unsigned short port;
       	struct servent *serventry = NULL;
	addr->sin_family = AF_INET;
	get_addr_struct(host, addr);
	
	printf("hostname: %s, IPADDR : %s\n",host, inet_ntoa(addr->sin_addr));

	/* assume service was specified by port number */
	port  = (unsigned short)atoi(service);

	if(port > 0){
		/* success , service port specified by number */
		addr->sin_port = htons(port);
	}else{
		/* failed : service was probably specified by name, look it up */
		serventry = getservbyname(service, proto);

		if(!serventry){
			fprintf(stderr, "Failed to get service port : %s\n",service);
			return 1;
		}
		addr->sin_port = serventry->s_port;


	}	
	return 0;
	
}
int main(int argc, char *argv[]){

	char *host = DEFAULT_HOST;
	char *service = DEFAULT_SERVICE;
	char *protocol = DEFAULT_PROTOCOL;
	
	struct sockaddr_in addr;
	unsigned short port;
	unsigned long address;
	int err;
	
	if(argc > 1) 
		host = argv[1];	
	if(argc > 2) 
		service = argv[2];
	if(argc > 3) 
		protocol  = argv[3];

	err = resolve(host, service, protocol,&addr);
	if(!err){
		port = ntohs(addr.sin_port);
		address = ntohl(addr.sin_addr.s_addr);
		printf("sin_family = %12d\n",addr.sin_family);
		printf("sin_addr = %12lu( 0x%08lX) (%s)\n",address, address, inet_ntoa(addr.sin_addr));
		printf("sin_port = %12hu (0x%08hX)\n",port,port);
	}
	return err;


}
