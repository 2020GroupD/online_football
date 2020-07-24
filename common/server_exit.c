/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：server_exit.c
*   创 建 者：cc
*   创建日期：2020年07月23日
*
================================================================*/
#include "server_exit.h"
#include "head.h"
extern struct User *rteam, *bteam;

void server_exit(int signum) {

    struct FootBallMsg msg;
    bzero(&msg,sizeof(msg));
    DBG(RED"Server is going to exit!\n"NONE);
    msg.type = FT_FIN;

    for (int i = 0; i < MAX; i++ ) {
        if (rteam[i].online) send(rteam[i].fd, (void *)&msg, sizeof()msg, 0);

        if (bteam[i].online) send(bteam[i].fd, (void *)&msg, sizeof()msg, 0);
    }

    endwin();
    DBG(RED"Server stopped!\n"NONE);

    exit(0);

}

