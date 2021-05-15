#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

char buf[BUFSIZ];

void main(int argc, char *argv[])
{
	int src_fd, dest_fd, len, bytes=0, ret;

	if(argc != 3){
		fprintf(stderr, "%s\n", "usage: cpcom [source] [destination]");
		exit(EXIT_FAILURE);
	}

	len = BUFSIZ;
	src_fd = open(argv[1], O_RDONLY);
	if(src_fd == -1){
		perror("open");
		exit(EXIT_FAILURE);
	}
	while(len != 0 && (ret=read(src_fd, buf, len)) != 0){
		if(ret == -1){
			if(errno == EINTR)
				continue;
			perror("read");
			exit(EXIT_FAILURE);
		}
		bytes += ret;
	}

	close(src_fd);

	len = bytes;
	dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(dest_fd == -1){
		perror("open");
		exit(EXIT_FAILURE);
	}

	ret = write(dest_fd, buf, len);
	
	if(ret == -1){
		perror("write");
		exit(EXIT_FAILURE);
	}

	close(dest_fd);

	exit(EXIT_SUCCESS);
}