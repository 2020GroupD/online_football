/*************************************************************************
	> File Name: datatype.h
	> Author: 
	> Mail: 
	> Created Time: Tue 21 Jul 2020 09:21:06 AM CST
 ************************************************************************/

#ifndef _DATATYPE_H
#define _DATATYPE_H

struct Point {
    int x;
    int y;
};

struct User {
    int team;   // 0 red 1 blue
    int fd;     // user->connection
    char name[20];
    int online; // 1 online 0 outline
    int flag;   // disconnection time
    struct Point loc;
};

struct LogRequest {
    char name[20];
    int team;
    char msg[512];
};

struct LogResponse {
    int type;   // 0 OK 1 No
    char msg[512];
};



#endif
