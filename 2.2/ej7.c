#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
	umask(0027);
	int fd = open("file", O_CREAT, 0645);
	if (fd == -1)
		perror("Error");
	return 0;
}