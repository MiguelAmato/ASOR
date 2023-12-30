#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <file>", argv[1]);
		return 1;
	}
	struct stat buf;
	if (stat(argv[1], &buf)) {
		perror("stat");
		return 1;
	}
	char *str = strdup(argv[1]);
	if (!str) {
		perror("strdup");
		return 1;
	}
	char *str1 = strdup(argv[1]); 
	if (!str1) {
		perror("strdup");
		return 1;
	}
	if (S_ISREG(buf.st_mode)) {
		if (link(argv[1], strcat(str, ".hard")) == -1) {
			perror("link");
			free(str);
			free(str1);
			return 1;
		}
		if (symlink(argv[1], strcat(str1, ".sym")) == -1) {
			perror("symlink");
			free(str);
			free(str1);
			return 1;
		}
	}
	free(str);
	free(str1);
	return 0;
}