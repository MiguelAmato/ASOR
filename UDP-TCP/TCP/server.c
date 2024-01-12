#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 500

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s ip port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct addrinfo hints;
	struct addrinfo *result;
	int s;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Para TCP */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

	s = getaddrinfo(argv[1], argv[2], &hints, &result); // Obtienes la información de las direcciones ip y puerto
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
		Try each address until we successfully bind(2).
		If socket(2) (or bind(2)) fails, we (close the socket
		and) try the next address. */

    struct addrinfo *rp; // Puntero con el que miraras todas las direcciones obtenidas en result
    int sfd; // fd del socket
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1) // Si falla conectandose al socket, vuelve a intentarlo con la sig 
			continue;
		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) // Si conecta con alguna, termina la búsqueda
			break;
	}

	if (rp == NULL) { // En el caso de que esté a NULL significa que no existe ningun address con el que te puedas conectar
		fprintf(stderr, "Could not bind\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result); // No necesitas más el result, lo liberas

	struct sockaddr_storage peer_addr; // Se guarda en esto y luego se castea a aockaddr para que valga con IPv4 e IPv6
	socklen_t peer_addr_len; // Tamaño de la info
	ssize_t nread; // Bytes uqe se van a leer en cada mensaje
	char buf[BUF_SIZE] = {0}; // Donde se guardará cada mensaje que recive el servidor
    
    if (listen(sfd, 5) == -1) {
        perror("listen");
        return 1;
    }
	while (1) {
        peer_addr_len = sizeof(struct sockaddr);
		pid_t pid = fork();
		if (pid == 0) 
			return 0;
		int sd = accept(sfd, (struct sockaddr*)&peer_addr, &peer_addr_len);
		if (sd == -1) {
			perror("accept");
			return 1;
		}
		char host[NI_MAXHOST], service[NI_MAXSERV];
		s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST);
		if (s == 0)
			printf("Conectado %s:%s)\n", host, service);
		else
			fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

        while (nread = recv(sd, buf, BUF_SIZE, 0)) {
			printf("%s", buf);
			send(sd, buf, nread, 0);
		}
		close(sd);
	}
}