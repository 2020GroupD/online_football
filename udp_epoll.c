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







void del_event(int epollfd, int fd) {
    close(fd);
    epoll_ctf(epollfd, EPOLL_CTL_DEL, fd, NULL);
}

int udp_connect(struct sockaddr_in*client){
    int sockfd;
    if((sockfd=socket_create_udp(port))<0){
        perror("socket_create_udp()");
        exit(1);
    
    }
   if(connect(sockfd,(struct sockaddr*)&client,sizeof(client))==-1){
        perror("connect()");
        exit(1);

   }
   return sockfd;

}
