#include <sys/utsname.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	struct utsname buf;
	if (uname(&buf) != 0)
		perror("Uname error");
	printf("sysname: %s\n", buf.sysname);
	printf("nodename: %s\n", buf.nodename);
	printf("release: %s\n", buf.release);
	printf("version: %s\n", buf.version);
	printf("machine: %s\n", buf.machine);
	printf("domainname: %s\n", buf.__domainname);
	return 0;
}