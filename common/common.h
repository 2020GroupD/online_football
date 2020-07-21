/*************************************************************************
	> File Name: common.h
	> Author: 
	> Mail: 
	> Created Time: Tue 21 Jul 2020 10:12:51 AM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

extern char ans[512];

char *get_conf_value(const char *path, const char *key);
int socket_create_udp(int port);
int socket_udp();
void make_non_block(int fd);
void make_block(int fd);

#endif
