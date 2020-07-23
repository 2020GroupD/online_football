/*************************************************************************
	> File Name: server_re_draw.c
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2020 11:11:11 AM CST
 ************************************************************************/

#include "head.h"

extern struct User *rteam, *bteam;
extern WINDOW *Football, *Football_t, *Message;
extern struct BallStatus ball_status;
extern struct Bpoint ball;
extern struct Map court;

void re_draw_ball() {
    double vx = ball_status.v.x, vy = ball_status.v.y;
    double ax = ball_status.a.x, ay = ball_status.a.y;
    ball.x = ball.x + vx * TIME_INTERVAL + ax * TIME_INTERVAL * TIME_INTERVAL;
    ball.y = ball.y + vy * TIME_INTERVAL + ay * TIME_INTERVAL * TIME_INTERVAL;
    
    int flag_out = 0;
    if (ball.x == 0) {
        ball.x = 0;
        flag_out = 1;
    }
    if (ball.x > court.width) {
        ball.x = court.width;
        flag_out = 1;
    }
    if (ball.y == 0) {
        ball.y = 0;
        flag_out = 1;
    }
    if (ball.y > court.height) {
        ball.y = court.height;
        flag_out = 1;
    }

    if (flag_out) w_gotoxy_puts(Message, 0, 0, "BALL OUT!");

    w_gotoxy_putc(Football, (int)ball.x, (int)ball.y, 'o');
}

void re_draw_player(int team, char *name, struct Point *loc) {
    if (team) 
        wattron(Football_t, COLOR_PAIR(6));
    else
        wattron(Football_t, COLOR_PAIR(2));
    w_gotoxy_puts(Football_t, loc->x, loc->y, name);
}

void re_draw_team(struct User *team) {
    for (int i = 0; i < MAX; i++) {
        if (team[i].online == 1)
            re_draw_player(team[i].team, team[i].name, &team[i].loc);
    }
}

void re_draw() {
    re_draw_team(rteam);
    re_draw_team(bteam);
    re_draw_ball();
}
