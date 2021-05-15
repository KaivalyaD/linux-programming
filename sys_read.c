#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <errno.h>
#include <limits.h>

#define PLEDGE "/root/progs/robert_love/pledge.txt"

// bss-es
int file_descriptor;
char buffer[BUFSIZ];

ssize_t generic_blocking_super_read(int fd, void *buf, size_t len){
	ssize_t read_ret, this_ret=0;

	if(len > SSIZE_MAX){
	/*  since ret is signed, range of len (unsigned) should be restricted below
		the maximum value of ret for the call to read to return a definite value	*/
		
	//	this block makes the function 'super read'-able
		len = SSIZE_MAX;
	}

	while(len != 0 && (read_ret = read(fd, buf, len)) != 0){
		if(read_ret == -1){
			// some error occurs

			if(errno == EINTR){
				// a signal interrupts read() midway
				continue;  // resubmitting read()
			}
		/* 	if(errno == E_AGAIN){
				// only for non blocking read function
				// call some other function here to save time and resubmit read()
			}	*/

			// something even worse happened
			perror("read");  // printing the error to stdout in a consistent way
			
			exit(EXIT_FAILURE);
		}
		
		// no errors occur
		this_ret += read_ret;

		buf += read_ret;
		len -= read_ret;
	}

	return this_ret;
}

void print(const char *name, size_t len){
	char *buf = buffer;

	fprintf(stdout, "Read %d bytes from '%s':\n", len, name);
	fprintf(stdout, "%s\n", buf);
}

int main(int argc, const char *argv[]){
	ssize_t bytes_read;

	// use O_NONBLOCK to open file for reading that won't sleep if more data is awaited
	// file_descriptor = open("/root/Progs/pledge.txt", O_RDONLY | O_NONBLOCK);
	file_descriptor = open(PLEDGE, O_RDONLY);

	if(file_descriptor == -1){
		perror("open");
		exit(EXIT_FAILURE);
	}

	// reading <= sizeof(buffer) worth of bytes into buffer
	bytes_read = generic_blocking_super_read(file_descriptor, &buffer, sizeof(buffer));
	print(PLEDGE, bytes_read);

	if(close(file_descriptor) == -1){
		perror("close");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}