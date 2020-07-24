/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：server_send_all.h
*   创 建 者：cc
*   创建日期：2020年07月23日
*
================================================================*/
#ifndef _SERVER_SEND_ALL_H
#define _SERVER_SEND_ALL_H

void send_team(struct User *team, struct FootBallMsg *msg);
void send_all(struct FootBallMsg *msg);

#endif //SERVER_SEND_ALL_H
