#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/time.h>

#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s host port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

	s = getaddrinfo(argv[1], argv[2], &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol);
		if (sfd == -1)
			continue;
		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;                  /* Success */
		close(sfd);
	}

	if (rp == NULL) {               /* No address succeeded */
		fprintf(stderr, "Could not bind\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);           /* No longer needed */

	/* Read datagrams and echo them back to sender */

	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;
	ssize_t nread;
	char buf[BUF_SIZE];

	listen(sfd, 5);
	// Usamos el prefork
	while(1) {
		peer_addr_len = sizeof(struct sockaddr_storage);
		pid_t pid = fork();
		if (pid == 0)
			return 0;
		int sd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_len);

		while ((nread = recv(sd, buf, BUF_SIZE, 0)) > 0) {
			buf[nread] = '\0';
			id_t p = atoi(buf);
			errno = 0;
			int nice = getpriority(PRIO_PROCESS, p);
			if (errno != 0) {
				printf("No existe el pid %d\n", p);
				continue;
			}
			printf("PID[%d]: %d\n", p, nice);
			fflush(stdout);
			nread = sprintf(buf, "%d\n", nice);
			send(sd, buf, nread, 0);
		}
		close(sd);
	}
}