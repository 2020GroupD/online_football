/*************************************************************************
	> File Name: head.h
	> Author: 
	> Mail: 
	> Created Time: Tue 14 Jul 2020 11:37:24 AM CST
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/shm.h>
#include <ncurses.h>

#include "common.h"
#include "datatype.h"
#include "game_ui.h"
#include "sub_reactor.h"
#include "udp_epoll.h"
#include "thread_pool.h"
#include "color.h"

#define MAX         20
#define NTHREAD     5

#ifdef _D
#define DBG(fmt, args...) printf(fmt, ##args)
#else
#define DBG(fmt, args...) 
#endif

#endif
