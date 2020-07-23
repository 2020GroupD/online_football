/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：send_ctl.c
*   创 建 者：cc
*   创建日期：2020年07月23日
*
================================================================*/
#include "send_ctl.h"

extern int sockfd;
extern struct FootBallMsg ctl_msg; //也是个全局变量

void send_ctl() {
    if (ctl_msg.ctl.dirx || ctl_msg.ctl.diry)
        send(sockfd, (void *)&ctl_msg, sizeof(ctl_msg), 0);
    ctl_msg.ctl.dirx = ctl_msg.ctl.diry = 0;
}

