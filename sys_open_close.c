#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

// bss-es
int file_descriptor;

int main(int argc, const char *argv[]){
	// file_descriptor = open("/root/Progs/pledge.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// statement above has the same effect as the one below
	// file_descriptor = creat("/root/Progs/pledge.txt", 0644);

	// to not truncate the pledge (written thrice until now), use the following
	file_descriptor = open("/root/progs/robert_love/pledge.txt", O_RDONLY);

	if(file_descriptor == -1){
		perror("open");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "file was successfully opened\n");

	if(close(file_descriptor) == -1){
		perror("close");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "file was successfully closed\n");

	exit(EXIT_SUCCESS);
}