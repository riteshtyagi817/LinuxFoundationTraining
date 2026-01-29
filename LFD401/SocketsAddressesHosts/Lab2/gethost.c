#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define MAXHOSTNAME 255

char * getsocktype(int socktype){

	switch(socktype){
		case SOCK_STREAM: return "SOCK_STREAM";
		case SOCK_DGRAM: return "SOCK_DGRAM";
		case SOCK_RAW: return "SOCK_DRAW";
		case SOCK_RDM: return "SOCK_RDM";
		case SOCK_SEQPACKET: return "SOCK_SEQPACKET";
		case SOCK_DCCP: return "SOCK_DCCP";
		case SOCK_PACKET: return "SOCK_PACKET";
	}

	return "Unknown";

}
int main(int argc, char *argv[]){
	
	struct addrinfo *ainfo, *res;
	char *host;
	int rc;
	char hostname[MAXHOSTNAME];
	char ipaddr[64]; /* max length of an IPV6 address plus a bit */
	void *addr;
	struct protoent *proto;

	if(argc > 2){
		printf("\nusage: %s address, try again !\n",argv[0]);
		exit(EXIT_FAILURE);
	}	
	host = argv[1];
	rc = getaddrinfo(host, NULL, NULL, &ainfo);
	if(rc != 0){
		gai_strerror(rc);
		exit(EXIT_FAILURE);
	}
	/* loop over all the structures found , get ip address etc */
	res = ainfo;
	while(res){
		rc = getnameinfo(res->ai_addr, res->ai_addrlen,hostname,NI_MAXHOST,NULL,0,0);
		if(rc < 0)
			fprintf(stderr, "rc in getnameinfo: %s\n",gai_strerror(rc));
		
		if(res->ai_family == AF_INET)
			addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
		else
			addr = &((struct sockaddr_in6 *)res->ai_addr)->sin6_addr;
		printf("hostname: %s and IPADDR: %s\n",hostname, 
				inet_ntop(res->ai_family, addr, ipaddr, res->ai_addrlen));
		proto = getprotobynumber(res->ai_protocol);
		printf("	addrlen: %d socktype: %s(%d) protocol: %s(%d)\n",
				res->ai_addrlen,
				getsocktype(res->ai_socktype), res->ai_socktype,
				proto->p_name, res->ai_protocol);
		res = res->ai_next;


	}
	freeaddrinfo(ainfo);
	return EXIT_SUCCESS;

	

}

