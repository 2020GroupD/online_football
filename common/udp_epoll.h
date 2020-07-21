/*************************************************************************
	> File Name: udp_epoll.h
	> Author: qzh
 ************************************************************************/

#ifndef _UDP_EPOLL_H
#define _UDP_EPOLL_H
<<<<<<< HEAD:common/udp_epoll.h

extern int port;

void add_event_ptr(int epollfd, int fd, int events, struct User *user);
void del_event(int epollfd, int fd);
int udp_connect(struct sockaddr_in *server);
int udp_accept(int fd, struct User *user);


=======
extern int port;
void add_event_ptr(int epollfd, int fd, int events, struct User *user);
void del_event(int epollfd, int fd);
int udp_connect(struct sockaddr_in*client);
>>>>>>> 7061c64144d25232974ea19fe6ad592594d739fa:udp_epoll.h
#endif
