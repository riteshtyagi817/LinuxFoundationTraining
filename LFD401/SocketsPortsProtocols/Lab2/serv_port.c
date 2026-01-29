#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

#define ErrMsg(msg){ perror(msg); exit(errno);}

void printit(struct servent *s);

int main(int argc, char *argv[]){

		struct servent *result;
		char proto[4];
		short inport;
		int k;

		if(argc < 3){
			printf("\nUSAGE: %s Service PortNumber \n", argv[0]);
			exit(EXIT_FAILURE);
		}
		inport = (short)atoi(argv[2]);

		printf("Checking things out for service %s and port %d\n",argv[1],inport);

		strcpy(proto,"tcp");

		for(k = 0; k < 2;k++){
			if(k > 0)
				strcpy(proto, "udp");
			printf("Doing getservbyname for proto = %s\n",proto);
			result = getservbyname(argv[1], proto);
			if(!result)
				ErrMsg("getservbyname")
			
			printit(result);

			printf("Doing getservbyport for proto = %s\n",proto);
			result = getservbyport(htons(inport), proto);
			if(!result)
				ErrMsg("geservbyport")

			printit(result);

		}
		
		exit(EXIT_SUCCESS);


}
void printit(struct servent *s){

	int j;
	char **tmp;
	printf("name = %15s, port = %5d, proto = %4s\n",s->s_name, ntohs(s->s_port), s->s_proto);
	if(*s->s_aliases){
		for(j = 0, tmp = s->s_aliases; *tmp != NULL;j++, tmp++){
			printf("Aliases[%d] = %s ", j, *tmp);	
			printf("\n");

		}	

	}
	return;

}









