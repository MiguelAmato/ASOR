#include <time.h>
#include <stdio.h>

int main() {
	time_t t = time(0);
	if (t == -1)
		perror("ayuda");
	printf("%ld \n", t);
}