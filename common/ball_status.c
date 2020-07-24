/*************************************************************************
	> File Name: ball_status.c
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2020 11:17:27 AM CST
 ************************************************************************/

#include "head.h"

extern struct Bpoint ball;
extern struct BallStatus ball_status;

int can_kick(struct Point *loc, int strengh) {
    if (abs(loc->x - ball.x) > 3 || abs(loc->y - ball.y) > 3)
        return 0;

    double angle = atan( (ball.x - loc->x) / (ball.y - loc->y));
    ball_status.v.x += ACCELERATION * cos(angle) * KICK_TIME * strengh;
    ball_status.v.y += ACCELERATION * sin(angle) * KICK_TIME * strengh;
    return 1;
}
