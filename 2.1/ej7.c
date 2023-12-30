#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	printf("%ld\n", pathconf(".", _PC_LINK_MAX));
	printf("%ld\n", pathconf(".", _PC_PATH_MAX));
	printf("%ld\n", pathconf(".", _PC_NAME_MAX));
	return 0;
}