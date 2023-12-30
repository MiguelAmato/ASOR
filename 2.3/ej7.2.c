#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <command>\n", argv[0]);
		return 1;
	}
	if (execvp(argv[1], &argv[1]) == -1) {
		perror("execvp");
		return 1;
	}
	return 0;
}