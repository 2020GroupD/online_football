/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：client_recv.c
*   创 建 者：cc
*   创建日期：2020年07月24日
*
================================================================*/
#include "head.h"

extern int sockfd;

void *client_recv(void *arg) {
    while(1) {
        struct FootBallMsg msg;
        struct User user;
        bzero(&msg, sizeof(msg));
        recv(sockfd, (void*)&msg, sizeof(msg), 0);
        strcpy(user.name, msg.name);
        user.team = msg.team;
        if(msg.type & FT_HEART) {
            DBG(RED"HeartBeat from server\n"NONE);
            msg.type = FT_ACK;
            send(sockfd, (void*)&msg, sizeof(msg), 0);
        }
        else if(msg.type & FT_MSG) {
            DBG(GREEN"SERVER MSG:"NONE"%s\n", msg.msg);
            Show_Message(Message, &user, msg.msg, 0);
        }
        else if(msg.type & FT_WALL) {
               Show_Message(Message, &user, msg.msg, 0);//Show_Message(Message, NULL, msg.msg, 1)
        }
        else if(msg.type & FT_FIN) {
            DBG(RED"Server is going to stop!\n"NONE);
            close(sockfd);
            endwin();
            exit(0);
        }
        else if(msg.type & FT_MAP) {
            Show_Message(Message, NULL, "Football game refresh", 1);
            //parse_spirit(msg.msg, msg.size);
        }
        else{
            DBG(GREEN"Msg Unsurpport\n"NONE);
        }
    
    }

}
