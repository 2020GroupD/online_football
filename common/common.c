#include "common.h"
#include "head.h"
extern char ans[255];
char *get_conf_value(const char *path, const char *key) {
    FILE *fp = NULL;
    fp = fopen(path, "r");
    char line[255] = {0};
    int flag = 0;
    while (fgets(line, 255, fp)) {
        if (strstr(line, key) != NULL) {
            int i = strlen(key);
            while (line[i] == ' ') i++;
            if (line[i] == '=') {
                strncpy(ans, line + i + 1, strlen(line + i + 1));
                flag = 1;
                return ans;
            } else {
                continue;
            }
        }
    }
    if(flag == 0) printf("NO THIS CHOISE\n");
    return NULL;
}

int socket_create_udp(int port){
    int listener;
    if((listener=socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("socket()");
        exit(1);
    }

    struct sockaddr_in server;
    server.sin_port=htons(port);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htonl(INADDR_ANY);

    unsigned long opt=1;
    setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    
    if(bind(listener,(struct sockaddr*)&server,sizeof(server))<0){
        return -1;
    }
    return listener;

}

int socket_udp() {
	int sockfd;
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		return -1;
	}
	return sockfd;
}

void make_non_block(int fd) {
    unsigned long ul = 1;
    ioctl(fd, FIONBIO, &ul);
}

void make_block(int fd) {
    unsigned long ul = 0;
    ioctl(fd, FIONBIO, &ul);
}
