#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

volatile int salvar;

void *handler(int signal) {
	salvar = 1;
}

void *alarma(int signal) {
	salvar = 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <segs>", argv[0]);
		return 1;
	}
	int seg = atoi(argv[1]);
	char *comando = strdup("rm ");
	strcat(comando, argv[0]);

	signal(SIGUSR1, (void *) handler);
	signal(SIGALRM, (void *) alarma);
	sigset_t suspend;
	sigfillset(&suspend);
	sigdelset(&suspend, SIGALRM);
	sigdelset(&suspend, SIGUSR1);
	alarm(seg);
	printf("Es hora de salvar el programa\n");
	sigsuspend(&suspend);

	if (salvar) {
		printf("Salvaste el programa :D\n");
		return 0;
	}
	else {
		system(comando);
		printf("Nooooo murio\n");
	}
	return 0;	
}