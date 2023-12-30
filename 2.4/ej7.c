#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

	int ph[2]; // 0 extremo de lectura, 1 extremo de escritura
	int hp[2];

	if (pipe(ph) == -1) {
		perror("pipe");
		return 1;
	}
	if (pipe(hp) == -1) {
		perror("pipe");
		return 1;
	}

	pid_t pid = fork();

	if (pid == 0) { // lee padre, escribe hijo
		int cont = 0;
		close(ph[1]);
		close(hp[0]);
		if (dup2(ph[0], 0) == -1) {
			perror("dup2");
			return 1;
		}
		close(ph[0]);
		while (cont < 10) {
			char buff[100];
			read(0, buff, 100);
			write(1,buff, strlen(buff));
			++cont;
			if (cont < 10)
				write(hp[1], "1", 1);
			else
				write(hp[1], "q", 1);
		}
		close(hp[1]);
	}
	else { // lee hijo, escribe padre
		close(hp[1]);
		close(ph[0]);
		if (dup2(ph[1], 1) == -1) {
			perror("dup2");
			return 1;
		}
		close(ph[1]);
		char buff[100];
		char respuesta = '1';
		while (respuesta != 'q') {
			read(0, buff, 100);
			write(1, buff, strlen(buff));
			read(hp[0], &respuesta, 1);
		}
		close(hp[0]);
	}
	return 0;
}