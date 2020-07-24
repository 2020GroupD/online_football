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

struct Bpoint {
    double x;
    double y;
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

struct Map {
    int width;
    int height;
    struct Point start;
    int gate_width;
    int gate_height;
};

struct Aspeed {
    double x;
    double y;
};

struct Speed {
    double x;
    double y;
};

struct BallStatus {
    struct Speed v;
    struct Aspeed a;
    int by_team;
    char name[20];
    //pthread_mutex_t mutex;
};

struct Score {
    int red;
    int blue;
};

//the value of action
#define ACTION_KICK     0x01
#define ACTION_CARRY    0x02
#define ACTION_STOP     0x04
#define ACTION_DFL      0x08
struct Ctl {
    int action;
    int dirx;
    int diry;
    int strength;
};

//the value of type
#define FT_HEART    0x01
#define FT_ACK      0x02
#define FT_MSG      0x04
#define FT_WALL     0x08
#define FT_CTL      0x10
#define FT_MAP      0x20
#define FT_FIN      0x40
#define FT_SCORE    0x80
#define FT_GAMEOVER 0x100

struct FootBallMsg {
    int type;
    int size;
    int team;
    char name[20];
    char msg[512];
    struct Ctl ctl;
};

#endif
