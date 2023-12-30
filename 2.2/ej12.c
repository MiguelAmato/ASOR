#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Error\n");
		return 1;
	}
	int fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	if (dup2(fd, 1) == -1) { // EJ 12
		perror("dup2");
		return 1;
	}
	if (dup2(fd, 2) == -1) { // EJ 13
		perror("dup2");
		return 1;
	}
	write(1, "Hola1", 5);
	perror("Hola2");
	close(fd);
	return 0;
}