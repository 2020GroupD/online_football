/*************************************************************************
	> File Name: udp_epoll.h
	> Author: qzh
 ************************************************************************/

#ifndef _UDP_EPOLL_H
#define _UDP_EPOLL_H

extern int port;

void add_event_ptr(int epollfd, int fd, int events, struct User *user);
void del_event(int epollfd, int fd);
int udp_connect(struct sockaddr_in *server);
int udp_accept(int fd, struct User *user);


#endif
