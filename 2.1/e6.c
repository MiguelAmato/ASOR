 #include <unistd.h>
 #include <stdio.h>

 int main() {
	printf("ARG MAX: %ld\n", sysconf(_SC_ARG_MAX));
	printf("CHILD MAX: %ld\n", sysconf(_SC_CHILD_MAX));
	printf("OPEN MAX: %ld\n", sysconf(_SC_OPEN_MAX));
 }