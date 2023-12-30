#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <command>\n", argv[0]);
		return 1;
	}
	system(argv[1]);
	return 0;
}