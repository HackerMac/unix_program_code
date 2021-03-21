#include "apue.h"
#include <sys/wait.h>

int main (void) {
	char buf[MAXLINE];	/* from apue.h*/
	pid_t pid;
	int status;
	
	printf("%% ");          /* */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;

		if (pid == fork() < 0) {	// create child faild
			err_sys("fork error\n");
		} else if (pid == 0) {		// child fork
			execlp(buf, buf, (char*)0);
			err_ret("couldn't execute: %s\n", buf);
			exit(127);
		}

		/* parent fork*/
		if ((pid == waitpid(pid, &status, 0)) < 0) err_sys("waitpid error\n");
		printf("%% ");
	}
	exit(0);
}
