#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main() {
	int fd = open("file", O_RDWR);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	if (lockf(fd, F_LOCK, 0) == -1) {
		perror("lock");
		return 1;
	}
	time_t t = time(NULL);
	printf("%s\n", ctime(&t));
	sleep(10);
	if (lockf(fd, F_ULOCK, 0) == -1) {
		perror("lock");
		return 1;
	}
	sleep(10);
	return 0;
}