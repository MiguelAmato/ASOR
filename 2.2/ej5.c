#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
	int fd;
	if ((fd = open("file", O_CREAT, 0645)) == -1)
		perror("Error");
}