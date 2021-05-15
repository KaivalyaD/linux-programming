#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

void main(void)
{
	pid_t child_pid, ret_pid;
	int child_status;

	switch((child_pid=fork())){
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);

		case 0:
			fprintf(stdout, "Child Here: \n%s: %d\n%s: %d", "ID", getpid(), "Parent ID", getppid());
			break;

		default:
			ret_pid = wait(&child_status);
			fprintf(stdout, "\nParent Here:\n%s: %d\n%s: %d", "ID", getpid(), "Child exited with status", child_status);
			break;
	}

	// this scope is also accessible to the child iff it doesn't call any exec() varients
	fprintf(stdout, "\n%s\n", "Guess Who?");
	exit(EXIT_SUCCESS);
}