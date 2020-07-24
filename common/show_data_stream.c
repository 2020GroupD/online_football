#include "head.h"

char data_stream[20];
WINDOW *Help;
struct Map court;

void show_data_stream(char type) {
	
	for (int i = 17; i > 0; i--) {
		data_stream[i + 1] = data_stream[i;
	}
	data_stream[1] = type;

	for (int i = 1; i < 19; i++) {
		switch(data_stream[i]) {
			case 'l'://login
				wattron(Help, COLOR_PAIR(1));
				break;
			case 'c'://carry
				wattron(Help, COLOR_PAIR(2));
				break;
			case 'k'://kick
				wattron(Help, COLOR_PAIR(3));
				break;
			case 's'://stop
				wattron(Help, COLOR_PAIR(4));
				break;
			case 'n'://normal
				wattron(Help, COLOR_PAIR(5));
				break;
			case 'e'://exit
				wattron(Help, COLOR_PAIR(6));
				break;
			default:
				break;
		}
	}
	w_gotoxy_putc(Help, i, court.height, ' ');
	//输出空格
}

