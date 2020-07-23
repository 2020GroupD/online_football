/*************************************************************************
	> File Name: udp_epoll.h
	> Author: qzh
 ************************************************************************/

#ifndef _UDP_EPOLL_SYH_H
#define _UDP_EPOLL_SYH_H


extern int port;
//syh
extern struct User *bteam, *rteam;
extern pthread_mutex_t bmutex, rmutex;
extern int bepollfd, repollfd;
//syh


int check_online(struct LogRequest *request);
int udp_accept(int fd, struct User *user);
void add_event_ptr(int epollfd, int fd, int events, struct User *user);
void del_event(int epollfd, int fd);
int udp_connect(struct sockaddr_in *server);
#endif
