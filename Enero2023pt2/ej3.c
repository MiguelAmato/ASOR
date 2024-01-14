#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 500

int main(void) {
	fd_set rfds;
	int fd1 = open("fifo1", O_RDONLY | O_NONBLOCK);
	int fd2 = open("fifo2", O_RDONLY | O_NONBLOCK);
	int buf[MAX];
	while (1) {
		FD_ZERO(&rfds);
		FD_SET(fd1, &rfds);
		FD_SET(fd2, &rfds);
		int retval = select(fd2 + 1, &rfds, NULL, NULL, NULL);
		if (retval == -1) {
			perror("select()");
			return 1;
		}
		else if (FD_ISSET(fd1, &rfds)) {
			write(1, "fifo1: ", 7);
			int aux = read(fd1, buf, MAX);
			buf[aux] = '\0';
			write(1, buf, aux);
			close(fd1);
			fd1 = open("fifo1", O_RDONLY | O_NONBLOCK);
		}
		else if (FD_ISSET(fd2, &rfds)) {
			write(1, "fifo2: ", 7);
			int aux = read(fd2, buf, MAX);
			buf[aux] = '\0';
			write(1, buf, aux);
			close(fd2);
			fd2 = open("fifo2", O_RDONLY | O_NONBLOCK);
		}
	}
	exit(EXIT_SUCCESS);
}