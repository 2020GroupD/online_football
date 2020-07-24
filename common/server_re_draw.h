/*************************************************************************
	> File Name: server_re_draw.h
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2020 11:09:03 AM CST
 ************************************************************************/

#ifndef _SERVER_RE_DRAW_H
#define _SERVER_RE_DRAW_H

void re_draw();
void re_draw_ball();
void re_draw_player(int team, char *name, struct Point *loc);
void re_draw_team(struct User *team);

#endif
