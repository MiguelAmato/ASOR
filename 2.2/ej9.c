#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int main(int argc, char *argv[]) {
	struct stat buf;
	if (stat(argv[1], &buf))
		perror("Error");
	printf("ID of containing device:  [%lx,%lx]\n", (long) major(buf.st_dev), (long) minor(buf.st_dev));
	printf("i Nodo: %lu\n", buf.st_ino);
	printf("Tipo: %o\n", buf.st_mode);
	printf("Last file access: %s", ctime(&buf.st_atime));
	
}