#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int main() {
	sigset_t blk_set;

	sigemptyset(&blk_set);
	sigaddset(&blk_set, SIGINT);
	sigaddset(&blk_set, SIGTSTP);

	sigprocmask(SIG_BLOCK, &blk_set, 0);

	sleep(atoi(getenv("SLEEP_SECS")));

	sigset_t p;
	sigpending(&p);

	if (sigismember(&p, SIGINT)) {
		printf("SIGINT\n");
	}
	else if (sigismember(&p, SIGTSTP)) { // Me parece mas correcto hacer un nuevo conjunto y desbloquear las que quieras a tener que borrar del original
		printf("SIGTSTP\n");
		sigset_t del; 
		sigemptyset(&del);
		sigaddset(&del, SIGTSTP);
		sigprocmask(SIG_UNBLOCK, &del, 0);
	}

	printf("fin\n");
}