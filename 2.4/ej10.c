#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX 256

int main(int argc, char *argv[]) {
	int fd1 = open("eyyo", O_RDONLY | O_NONBLOCK);
	int fd2 = open("yoyo", O_RDONLY | O_NONBLOCK);

	char buffer[MAX];
	fd_set set;
	FD_ZERO(&set);
	FD_SET(fd1, &set);
	FD_SET(fd2, &set);

	int max = fd1;
	if (fd2 > max)
		max = fd2;
	
	while (1) {
		FD_ZERO(&set);
		FD_SET(fd1, &set);
		FD_SET(fd2, &set);
		int retval = select(max + 1, &set, 0, 0, 0);
		if (retval == -1) {
			perror("select");
			return 1;
		}
		else if (retval) {
			if (FD_ISSET(fd1, &set)) {
				write(1,"eyyo: ", 6);
				int aux = read(fd1,buffer, MAX);
				buffer[aux - 1] = '\0';
				write(1,buffer,aux);
				fd1 = open("eyyo", O_RDONLY | O_NONBLOCK);
			}
			else if (FD_ISSET(fd2, &set)) {
				write(1,"yoyo: ", 6);
				int aux = read(fd2,buffer, MAX);
				buffer[aux - 1] = '\0';
				write(1,buffer,aux);
				close(fd2);
				fd2 = open("yoyo", O_RDONLY | O_NONBLOCK);
			}
			write(1,"\n",1);
		}
	}
	return 0;
}