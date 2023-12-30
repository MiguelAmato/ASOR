#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sched.h>

// SI HACES sudo -i Y LO DEL EJERCICIO ANTERIOR TE DARA FIFO 12 

int main () {
	int p = sched_getscheduler(getpid()); 
	if (p == -1) {
		perror("scheduler");
		return 1;
	}
	if (p == SCHED_FIFO)
		write(1,"FIFO\n",5);
	else if (p == SCHED_OTHER)
		write(1,"OTHER\n",6);
	else if (p == SCHED_RR)
		write(1,"RR\n",3);
	
	struct sched_param sp;
	int prio = sched_getparam(getpid(), &sp);

	printf("%d\n", sp.sched_priority);
	
}