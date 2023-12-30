#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>   
#include <sys/stat.h>
#include <fcntl.h>

int demonio_archivos() {
	int fd1 = open("/tmp/daemon.out", O_WRONLY | O_CREAT);
	int fd2 = open("/tmp/daemon.err", O_RDWR | O_CREAT);
	int fd3 = open("/dev/null", O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1) {
		perror("error");
		return 1;
	}
	if (dup2(fd1, 1) == -1) {
		perror("dup2");
		return 1;
	}
	if (dup2(fd2, 2) == -1) {
		perror("dup2");
		return 1;
	}
	if (dup2(fd3, 0) == -1) {
		perror("dup2");
		return 1;
	}
	return 0;
}

int demonio_exe(char *argv[]) {
	if (execvp(argv[1], &argv[1]) == -1) {
		perror("execvp");
		return 1;
	}
	return 0;
}

int main (int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <command>\n", argv[0]);
		return 1;
	}
	pid_t pid = fork();
	if (pid == 0) {
		if (demonio_archivos() == 1)
			return 1;
		pid_t p_demonio = fork();
		if (p_demonio == 0) {
			pid_t sesion = setsid();
			return demonio_exe(argv);
		}
		else
			wait(0);
	}
	else 
		wait(0);
	return 0;
}