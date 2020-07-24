/*************************************************************************
	> File Name: game_ui.c
	> Author: 
	> Mail: 
	> Created Time: Wed 22 Jul 2020 10:34:33 AM CST
 ************************************************************************/

#include "head.h"
extern int messsage_num;
void Show_Message(WINDOW *win, struct User *user, char *msg, int type) {
    time_t time_now = time(NULL);
    struct tm* tm = localtime(&time_now);
    char timestr[20] = {0};
    char username[80] = {0};
    sprintf(timestr, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
    if (type) {
        wattron(win, COLOR_PAIR(4));
        strcpy(username, "Server Info : ");
    } else {
        if (user->team)
            wattron(win, COLOR_PAIR(6));
        else
            wattron(win, COLOR_PAIR(2));
        sprintf(username, "%s : ", user->name);
    }

    if (messsage_num <= 4) {
        w_gotoxy_puts(win, 10, messsage_num, username);
        wattron(win, COLOR_PAIR(3));
        w_gotoxy_puts(win, 10 + strlen(username), messsage_num, msg);
        wattron(win, COLOR_PAIR(5));
        w_gotoxy_puts(win, 1, messsage_num, timestr);
        messsage_num++;
    } else {
        messsage_num = 4;
        scroll(win);
        w_gotoxy_puts(win, 10, messsage_num, username);
        wattron(win, COLOR_PAIR(3));
        w_gotoxy_puts(win, 10 + strlen(username), messsage_num, msg);
        wattron(win, COLOR_PAIR(5));
        w_gotoxy_puts(win, 1, messsage_num, timestr);
        messsage_num++;
    }
    wrefresh(win);
}

WINDOW *create_newwin(int width, int heigth, int startx, int starty) {
    WINDOW *win;
    win = newwin(heigth, width, starty, startx);
    box(win, 0, 0);
    wrefresh(win);
    return win;
}

void destroy_win(WINDOW *win) {
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}

void gotoxy(int x, int y) {
    move(y, x);
}

void gotoxy_putc(int x, int y, int c) {
    move(y, x);
    addch(c);
    move(LINES - 1, 1);
    refresh();
}

void gotoxy_puts(int x, int y, char* s) {
    move(y, x);
    addstr(s);
    move(LINES - 1, 1);
    refresh();
}

void w_gotoxy_putc(WINDOW *win, int x, int y, int c) {
    mvwaddch(win, y, x, c);
    move(LINES - 1, 1);
    wrefresh(win);
}

void w_gotoxy_puts(WINDOW *win, int x, int y, char *s) {
    mvwprintw(win, y, x, s);
    move(LINES - 1, 1);
    wrefresh(win);
}

void initfootball() {
    initscr();
    clear();
    if (!has_colors() || start_color() == ERR) {
        endwin();
        fprintf(stderr, "终端不支持颜色!\n");
        exit(1);                                    
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK); //绿色
    init_pair(2, COLOR_RED, COLOR_BLACK);//红色
    init_pair(3, COLOR_WHITE, COLOR_BLACK);//白色
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);//黄色
    init_pair(5, COLOR_CYAN, COLOR_BLACK);//青色
    init_pair(6, COLOR_BLUE, COLOR_BLACK);//蓝色
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK); //洋红
    init_pair(8, COLOR_BLACK, COLOR_GREEN);
    init_pair(9, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(10, COLOR_BLACK, COLOR_RED);
    init_pair(11, COLOR_BLACK, COLOR_BLUE);
    init_pair(12, COLOR_BLACK, COLOR_YELLOW);
    Football_t = create_newwin(court.width + 4, court.height + 2, court.start.x - 2, court.start.y - 1);
    //Football = create_newwin(court.width + 4, court.height + 4, court.start.x - 2, court.start.y - 2);
    Football = subwin(Football_t, court.height, court.width, court.start.x, court.start.y);
    WINDOW *Message_t = create_newwin(court.width + 4, 7,  court.start.x - 2, court.start.y + court.height + 1);
    Message = subwin(Message_t, 5, court.width + 2, court.start.y + court.height + 2 , court.start.x - 1);
    scrollok(Message, 1);
    Help = create_newwin(20, court.height + 2,  court.start.x + court.width + 2, court.start.y - 1);
    Score = create_newwin(20, 7,  court.start.x + court.width + 2 , court.start.y + court.height + 1);
    Write = create_newwin(court.width + 4 + 20, 5,  court.start.x - 2, court.start.y + 1 + court.height + 7);
    box(Write, 0, 0);
    wattron(Football, COLOR_PAIR(6));
    w_gotoxy_putc(Football, ball.x, ball.y, 'o');
}

