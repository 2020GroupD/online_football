/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：heart_beat.c
*   创 建 者：cc
*   创建日期：2020年07月23日
*
================================================================*/
#include "heart_beat.h"
#include "head.h"
#define HEART_TIME 1000
extern struct User *rteam, *bteam;
extern int repollfd, bepollfd;
struct FootBallMsg heart_msg;

void heart_beat_team(struct User *team) {
	
	for(int i = 0; i < MAX; i++ ) {
		if(team[i].online) {
			send(team[i].fd, (void*)&heart_msg, sizeof(heart_msg), 0);
			team[i].flag--;
		}
	}
	for(int i = 0; i < MAX; i++){
		if(team[i].flag == 0) {
			team[i].online = 0;
			if(team[i].team == 1){
				del_event(bepollfd, team[i].fd);
			}
			else {
				del_event(repollfd, team[i].fd);
			}
	    }
	    //遍历team数组，判断在线，则发送FT_HEART心跳包，flag--
        //判断palyer的flag是否减为0，减为0则判断为下线
        //数组中标记为offline-->online = 0
        //在从反应堆中注销IO  //del_event
    }
}
void *heart_beat(void *arg) {
    //死循环，固定时间调用heart_beat_team
    heart_msg.type = FT_HEART;
	while(1){
		sleep(HEART_TIME);
		heart_beat_team(rteam);
		heart_beat_team(bteam);
	}
}

