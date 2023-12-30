#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

int main() {
	if (setuid(0) == -1)
		perror("error");
	return 1;
}