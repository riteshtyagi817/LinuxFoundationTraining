#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>
#include<sys/inotify.h>
#include<string.h>
#define check(e,m,flg) if(e & m) printf("mask includes %s\n",flg)
int main(int argc, char *argv[]){

	int fd = 0,bytes_read = 0,offset = 0, bufsize = 0;
	char *buf = NULL;
	struct inotify_event *ev = NULL;

	bufsize = getpagesize();
	buf = malloc(bufsize);
	printf("Size of inotify event = %ld.\n",sizeof(struct inotify_event));
	fd = inotify_init();

	printf("inotify_add_watch = %d\n",inotify_add_watch(fd,"/tmp",IN_ALL_EVENTS));

	while(1){


		offset  = 0;
		memset(buf, '\0',bufsize);
		bytes_read = read(fd, buf, bufsize);
		printf("Bytes read %d\n",bytes_read);
		while(offset < bytes_read){

			ev = (struct inotify_event *)(buf + offset);
			printf("Event: wd = , %d, mask = %x,cookie = %d,len = %d, name = %s\n",ev->wd,ev->mask,ev->cookie, 
					ev->len, ev->name);
			check(ev->mask,IN_ACCESS,"IN_ACCESS");
			check(ev->mask,IN_ATTRIB,"IN_ATTRIB");
			check(ev->mask,IN_CLOSE_WRITE,"IN_CLOSE_WRITE");
			check(ev->mask,IN_CLOSE_NOWRITE,"IN_CLOSE_NOWRITE");
			check(ev->mask,IN_CREATE,"IN_CREATE");
			check(ev->mask,IN_DELETE,"IN_DELETE");
			check(ev->mask,IN_DELETE_SELF,"IN_DELETE_SELF");
			check(ev->mask,IN_MODIFY,"IN_MODIFY");
			check(ev->mask,IN_MOVE_SELF,"IN_MOVE_SELF");
			check(ev->mask,IN_MOVED_FROM,"IN_MOVED_FROM");
			check(ev->mask,IN_MOVED_TO,"IN_MOVED_TO");
			check(ev->mask,IN_OPEN,"IN_OPEN");
			offset += sizeof(struct inotify_event) + ev->len;

		}

	}


	#if 0
	char buf[4096];
	memset(buf, '\0', sizeof(buf));
	uint32_t mask = IN_ACCESS|IN_ATTRIB||IN_CREATE|IN_DELETE;
	i_watch = inotify_add_watch(fd,"/tmp",mask);
	#endif
	
	exit(EXIT_SUCCESS);
}
