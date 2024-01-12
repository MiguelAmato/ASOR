#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Uso: %s <direccion>\n", argv[0]);
		return 1;
	}
	struct addrinfo *af;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	if(getaddrinfo(argv[1], 0, &hints, &af) != 0) {
		perror("getaddrinfo");
		return 1;
	}
	while (af) {
		char buff[100];
		if (getnameinfo(af->ai_addr,af->ai_addrlen, buff, 100, 0, 0, NI_NUMERICHOST)) {
			perror("getnameinfo");
			return 1;
		}
		printf("%s %d %d\n", buff, af->ai_family, af->ai_socktype);  
		af = af->ai_next;              
	}
}