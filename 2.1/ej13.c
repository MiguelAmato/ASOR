#include <time.h>
#include <stdio.h>
#include <sys/time.h>

int main() {
	struct timeval tv;

	gettimeofday(&tv, 0);
	long long unsigned int primera = tv.tv_usec;

	for (int i = 0; i < 1000000; ++i);

	gettimeofday(&tv, 0);
	long long unsigned int segunda = tv.tv_usec;

	printf("%llu\n", segunda - primera);
}