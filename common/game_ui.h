/*************************************************************************
	> File Name: game_ui.h
	> Author: 
	> Mail: 
	> Created Time: Wed 22 Jul 2020 10:34:54 AM CST
 ************************************************************************/

#ifndef _GAME_UI_H
#define _GAME_UI_H

extern struct Map court;    //球场大小，你应该在server.c和client.c中定义该变量，并初始化
extern WINDOW *Football, *Football_t, *Message, *Help, *Score, *Write;//窗体
extern struct Bpoint ball;  //球的位置
extern struct BallStatus ball_status;

void Show_Message(WINDOW *win, struct User *user, char *msg, int type);
WINDOW *create_newwin(int width, int heigth, int startx, int starty);
void destroy_win(WINDOW *win);
void gotoxy(int x, int y);
void gotoxy_putc(int x, int y, int c);
void gotoxy_puts(int x, int y, char* s);
void w_gotoxy_putc(WINDOW *win, int x, int y, int c);
void w_gotoxy_puts(WINDOW *win, int x, int y, char *s);
void initfootball();

#endif
