#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main () {
	uid_t uid =  getuid();
	uid_t euid = geteuid();

	printf("uid: %u\n", getuid());
	printf("euid: %u\n", geteuid());
}