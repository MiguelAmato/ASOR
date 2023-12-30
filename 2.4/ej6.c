#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 5) {
		printf("Uso: <comando1> <arg1> <comando2> <arg2>\n");
		return 1;
	}

	char *c1 = argv[1];
	char *a1 = argv[2];
	char *c2 = argv[3];
	char *a2 = argv[4];

	int fd[2]; // 0 extremo de lectura, 1 extremo de escritura

	if (pipe(fd) == -1) {
		perror("pipe");
		return 1;
	}

	pid_t pid = fork();

	if (pid == 0) { // Extremo de lectura
		if (dup2(fd[0], 0) == -1) {
			perror("dup2");
			return 1;
		}
		close(fd[1]);
		close(fd[0]);
		execlp(c2, c2, a2, NULL);
	}
	else { // Extremo de escritura
		if (dup2(fd[1], 1) == -1) {
			perror("dup2");
			return 1;
		}
		close(fd[0]);
		close(fd[1]);
		execlp(c1, c1, a1, NULL);
	}
	return 0;
}