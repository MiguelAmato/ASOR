#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Uso: %s <Mensaje>\n", argv[0]);
		return 1;
	}
	int fd = open("eyyo", O_WRONLY);
	write(fd, argv[1], strlen(argv[1]));
	close(fd);
	return 0;
}