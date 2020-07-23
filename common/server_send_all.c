/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：server_send_all.c
*   创 建 者：cc
*   创建日期：2020年07月23日
*
================================================================*/
#include "server_send_all.h"

extern struct User *rteam, *bteam;

void send_team(struct User *team, struct FootBallMsg *msg){

    for (int i = 0; i < MAX; i++) {

        if (team[i].online) send(team[i].fd, (void *)msg, sizeof(struct FootBallMsg), 0);

    }

}

void send_all(struct FootBallMsg *msg) {

    send_team(rteam, msg);

    send_team(bteam, msg);

}

