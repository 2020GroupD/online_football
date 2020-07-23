/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：send_chat.c
*   创 建 者：cc
*   创建日期：2020年07月23日
*
================================================================*/
#include "send_chat.h"

extern int sockfd;
extern WINDOW *Write;
extern struct FootBallMsg chat_msg;
void send_chat() {
    echo();
    nocbreak();
    bzero(chat_msg.msg, sizeof(chat_msg.msg));
    w_gotoxy_puts(Write, 1, 1, "Input Message : ");
    mvwscanw(Write, 2, 1, "%[^\n]s", chat_msg.msg);
    if (strlen(chat_msg.msg))
        send(sockfd, (void *)&chat_msg, sizeof(chat_msg), 0);
    wclear(Write);
    box(Write, 0, 0);
    wrefresh(Write);
    noecho();
    cbreak();

}

