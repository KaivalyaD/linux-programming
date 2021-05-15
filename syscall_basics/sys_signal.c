#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

int cnt = 0;

void useless_handler(int);

int main(void){
	if(signal(SIGINT, useless_handler) == (void *)-1){
		perror("signal");
		exit(EXIT_FAILURE);
	}

	while(1){
		fprintf(stdout, "%d\n", cnt);
		cnt += 1;
		sleep(1);
	}

	// does not exit unless SIGKILL;
}

void useless_handler(int signum){
	fprintf(stdout, "%s: %d\n", "PID", getpid());
	fprintf(stdout, "%d: %s: %d\n", cnt, "Received signal Number", signum);
}