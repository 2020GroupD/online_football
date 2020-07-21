/*************************************************************************
	> File Name: udp_epoll.c
	> Author: qzh
 ************************************************************************/

#include "head.h"
#include "udp_epoll.h"

void add_event_ptr(int epollfd, int fd, int events, struct User *user) {
    struct epoll_event ev;
    //调用epoll_ctf将fd加入到epollfd中
    ev.data.ptr = user;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        perror("epoll_ctl()");
        return ;
    }
    return ;
}


int udp_connect(struct sockaddr_in *server) {
    int sockfd = socket_create_udp(port);

    if (sockfd < 0) {
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(*server)) < 0) {
        return -1;
    }

    return sockfd;
}  

int udp_accept(int fd, struct User *user) {
    int new_fd, ret;
    struct sockaddr_in client;
    struct LogRequest request;
    struct LogResponse response;
    socklen_t len = sizeof(client);
    
    bzero(client, sizoef(client));
    bzero(request, sizeof(request));
    bzero(response, sizeof(response));

    ret = recvfrom(fd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, &len);
    
    if (ret != sizeof(response)) {
        response.type = 1;
        char *msg = "Login failed with Data errors";
        sprintf(response.msg, msg);
        send(fd, response, sizeof(response), 0);
        return -1;
    }
    
    new_fd = udp_connect(&client);
    if (new_fd < 0) {
        return -1;
    }
    
    sprintf(user->name, request.name);
    sprintf(user->msg, request.msg);
    user->team = request.team;
    
    char *msg = "Login Success, Enjoy Yourself";
    send(fd, msg, strlen(msg), 0);

    return new_fd;
}

void del_event(int epollfd, int fd) {
    close(fd);
    epoll_ctf(epollfd, EPOLL_CTL_DEL, fd, NULL);
}
