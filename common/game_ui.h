#ifndef _GAME_UI_H
#define _GAME_UI_H

extern struct Map court;
extern WINDOW *Football, *Football_t, *Message, *Help, *Score, *Write;
extern struct Bpoint ball;
extern struct BallStatus ball_status;

WINDOW *creat_newwin(int width, int height, int startx, int starty);
void destroy_win(WINDOW *win);
void gotoxy(int x, int y);
void gotoxy_putc(int x, int y, int c);
void gotoxy_puts(int x, int y, char *s);
void w_gotoxy_putc(WINDOW *win, int x, int y, int c);
void w_gotoxy_puts(WINDOW *win, int x, int y, char *s);
void initfootball();

#endif
