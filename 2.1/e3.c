#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main() {
	for (int i = 0; i < 255; ++i)
		printf("%d: %s\n",i, strerror(i));
	return 1;
}