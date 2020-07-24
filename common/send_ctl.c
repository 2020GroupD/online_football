/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：send_ctl.c
*   创 建 者：cc
*   创建日期：2020年07月23日
*
================================================================*/
#include "send_ctl.h"
#include "head.h"
extern int sockfd;
extern struct FootBallMsg ctl_msg; //也是个全局变量
extern WINDOW *Message;
void send_ctl() {

    if (ctl_msg.ctl.dirx || ctl_msg.ctl.diry){
        ctl_msg.ctl.action = ACTION_DFL;
        send(sockfd, (void *)&ctl_msg, sizeof(ctl_msg), 0);
        Show_Message(Message, NULL, "SEND CTLLLLLL\n", 1);
        ctl_msg.ctl.dirx = ctl_msg.ctl.diry = 0;
        show_data_stream('n');
    }
}

