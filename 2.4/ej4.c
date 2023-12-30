#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

volatile int c = 0, z = 0;

void *handler(int signal) {
	if (signal == SIGINT)
		++c;
	else if (signal == SIGTSTP)
		++z;
}

int main() {
	struct sigaction action;
	action.sa_handler = (void *) handler;

	sigaction(SIGINT, &action, 0);
	sigaction(SIGTSTP, &action, 0);

	while (c + z < 10);

	printf("^C: %d, ^Z: %d", c, z);
}