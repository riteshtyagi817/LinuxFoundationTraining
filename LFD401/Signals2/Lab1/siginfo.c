#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#define ErrMsg(msg) { perror(msg); exit(errno);}

struct my_s{
	int x;
	char s[32];
};

/* Signal handler */
void sig_act(int sig, siginfo_t *si,void *a){

	printf("In handler pid = %d, SIGNAL = %d\n",getpid(), sig);

	printf("si_signo = \t%d\n",si->si_signo);
	printf("si_code = \t%d\n",si->si_code);
	printf("si_pid = \t%d\n",si->si_pid);
	printf("si_uid = \t%d\n",si->si_uid);

	if(si->si_ptr){

		struct my_s *s = si->si_ptr;
		printf("si_ptr.x = \t%d\n",s->x);
		printf("si_ptr.s = \t%s\n",s->s);

	}
	return;
}
int main(int argc, char *argv[]){




	struct sigaction act;
	struct my_s s;
	int j, sig = SIGINT;
	union sigval sv;

	if(argc > 1)
		sig = atoi(argv[1]);

	memset(&act, '\0',sizeof(act));
	act.sa_sigaction = sig_act;
	act.sa_flags = SA_SIGINFO;
	if(sigaction(sig, &act, NULL) < 0) /* Ctrl - C */
		ErrMsg("sigaction")

	printf("pid = %d successfully installed signal handler for signal = %d\n",getpid(), sig);
	for(j = 0; j < 3;j++){

		printf("This is a pointless message\n");
		s.x = j*100;
		strcpy(s.s, "hello buddy");
		sv.sival_ptr = &s;
		printf("siqueue returns %d\n",sigqueue(getpid(), sig, sv));
		sleep(1);
	}







	exit(EXIT_SUCCESS);


}
