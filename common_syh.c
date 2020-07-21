#include "common.h"


int socket_create_udp(int port) {
	int listener;
	if ((listener = socket(AF_INET, SOCK_DGRAM)) < 0) {
		return -1;
	}

	unsigned long opt = 1;
	if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		return -1;
	}

	make_non_block(listener);

	struct sockaddr_in server;
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.port = htons(port);

	if (bind(listener, (struct sockaddr *)&server, sizeof(server)) < 0) {
		return -1;
	}
	return listener;
}


int socket_udp() {
	int sockfd;
	if((sockfd = socket(AF_INET, SOCK_DGRAM)) < 0){
		return -1;
	}
	return sockfd;
}
//

