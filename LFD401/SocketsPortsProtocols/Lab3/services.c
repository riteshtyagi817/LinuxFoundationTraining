#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>

void printit(struct servent *s);

int main(int argc, char *argv[]){


	struct servent *result;
	setservent(0);

	while((result = getservent()))
			printit(result);
	endservent();
	exit(EXIT_SUCCESS);



}
void printit(struct servent *s){

	int j;
	char **tmp;

	printf("name = %15s, port = %5d, proto = %4s\n",s->s_name, ntohs(s->s_port),s->s_proto);

	if(*s->s_aliases) {
		for(j = 0, tmp = s->s_aliases;*tmp != NULL;j++,tmp++)
			printf(" aliases[%d] = %s\n", j, *tmp);
			printf("\n");
		
	}

	return;
	
}
