#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

int main () {

	pid_t pid = getpid(), ppid = getppid(), gid = getpgid(pid), sid = getsid(pid);
	printf("pid: %d, ppid: %d, gid: %d, sid: %d\n", pid, ppid, gid, sid);

	char buff[300];
	getcwd(buff, 300);
	printf("pwd: %s\n", buff);

	struct rlimit rlim;
	if (getrlimit(RLIMIT_NOFILE, &rlim) == -1) {
		perror("rlimit");
		return 1;
	}

	printf("limite: %ld\n", rlim.rlim_max);
}