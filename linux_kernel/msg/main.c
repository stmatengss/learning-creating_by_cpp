#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#define MSGSZ 128
#define KEY 6666

typedef struct msgbuf {
		long mtype;
		char mtext[MSGSZ];
} message_buf;

int main (int argc, char **argv) {

		int msqid;
		key_t key;
		message_buf sbuf;
		size_t buf_length;
		

		if (argc == 1) {
				int msgflag = IPC_CREAT | 0666;
				if ((msqid = msgget(KEY, msgflag) ) < 0 ) {
						perror("fuck\n");
						exit(-1);
				}

				fprintf(stderr, "msqid = %d\n", msqid);
				sbuf.mtype = 1;
				strcpy(sbuf.mtext, "Hello!\n");	
				fprintf(stderr, "sending\n");
				buf_length = strlen(sbuf.mtext) + 1;

				if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
						perror("fuck 2\n");
						exit(-1);
				}
		} else {
				int msgflag = 0666;
				if ((msqid = msgget(KEY, msgflag) ) < 0 ) {
						perror("fuck\n");
						exit(-1);
				}

				fprintf(stderr, "msqid = %d\n", msqid);
				fprintf(stderr, "recving\n");
				if (msgrcv(msqid, &sbuf, MSGSZ, 1, 0) < 0) {
						fprintf(stderr, "%s\n", strerror(errno));
						perror("fuck 3\n");
						exit(-1);
				}
				fprintf(stderr, "recv: %s", sbuf.mtext);
		}
		
		return 0;
}
