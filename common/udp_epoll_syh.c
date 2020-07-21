/*************************************************************************
	> File Name: udp_epoll.c
	> Author: qzh
 ************************************************************************/

#include "head.h"
#include "udp_epoll.h"

//syh
extern int port;
extern struct User *bteam, *rteam;
extern pthread_mutex_t bmutex, rmutex;
extern int bepollfd, repollfd;
//syh

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
        perror("udp_connect_socket_create()");
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(*server)) < 0) {
        perror("udp_connect_connect()");
        exit(1);
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


//syh 2020/7/21

int find_sub(struct User *team) {
	for (int i = 0; i < MAX; i++) {
		if (!team[i].online) return i;
	}
	return -1;
}


void add_to_sub_reactor(struct User *user) {
	struct User *team = (user->team ? bteam : rteam);
	if (user->team) {
		pthread_mutex_lock(&bmutex);
	} else {
		pthread_mutex_lock(&rmutex);
	}
	int sub = find_sub(team);
	if (sub < 0) return ;
	team[sub] = *user;
	team[sub].online = 1;
	team[sub].flag = 10;//10为默认设置
	
	if (user->team) {
		pthread_mutex_unlock(&bmutex);
	} else {
		pthread_mutex_unlock(&rmutex);
	}

	if (user->team) {
		add_event_ptr(bepollfd, team[sub].fd, EPOLLIN | EPOLLET, &team[sub]);

	} else {
		add_event_ptr(repollfd, team[sub].fd, EPOLLIN | EPOLLET, &team[sub]);
	}
}

//老师这里好像没有unlock而且lock unlock两次都是blue队
//syh 2020/7/21
