#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h> 

int main (int argc, char **argv) {
	if (argc != 3) {
		printf("Uso: %s comando1 comando2", argv[0]);
		return 1;
	}
	char *cmd1 = argv[1];
	char *cmd2 = argv[2];
	int fd[2]; // 0 lectura 1 escritura
	if (pipe(fd) == -1) {
		perror("pipe");
		return 1;
	}
	pid_t pid = fork();
	if (pid == 0) {
		fprintf(stdout, "Hijo: %d\n", getpid());
		close(fd[0]);
		if (dup2(fd[1], 1) == -1) {
			perror("dup2");
			return 1;
		}
		close(fd[1]);
		system(cmd1);
	}
	else {
		fprintf(stdout, "Padre: %d\n", getpid());
		close(fd[1]);
		if (dup2(fd[0], 0) == -1) {
			perror("dup2");
			return 1;
		}
		close(fd[0]);
		system(cmd2);
	}
}