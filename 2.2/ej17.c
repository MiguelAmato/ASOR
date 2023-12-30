#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage\n");
		return 1;
	}
	DIR *dir = opendir(argv[1]);
	struct dirent *d = readdir(dir); 
	while (d) {
		printf("%s", d->d_name);
		if (d->d_type == DT_REG) {
			struct stat s;
			stat(d->d_name, &s);
			if (s.st_mode & S_IXUSR == S_IXUSR || s.st_mode & S_IXGRP == S_IXGRP || s.st_mode & S_IXOTH == S_IXOTH)
				printf("*");
		}
		else if (d->d_type == DT_DIR) {
			printf("/");
		}
		else if (d->d_type == DT_LNK) {
			char buf[100];
			readlink(d->d_name, &buf, 100);
			printf("->%s", buf);
		}
		printf("\n");
		d = readdir(dir);
	}
}
