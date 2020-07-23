#include "head.h"


int port;
char *conf = "./footballd.conf";
char ans[512] = {0};
int bepollfd, repollfd;
struct Map court;
struct Bpoint ball;
struct BallStatus ball_status;

struct User *rteam, *bteam;
pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER;

int main (int argc, char **argv) {
	int opt, listener, epollfd;
	pthread_t red_t, blue_t, heart_t;
	while ((opt = getopt(argc, argv, "p:")) != -1) {
		switch (opt) {
			case 'p':
				port = atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage : %s -p port\n", argv[0]);
				exit(1);
		}
	
	}
	
	printf("1\n");

	bzero(&court, sizeof(court));
	bzero(&ball, sizeof(ball));
	bzero(&ball_status, sizeof(ball_status));	

	//判断一配置文件合法性，如果不做合法性判断，在下面一行容易出现bug
	if (!port) port = atoi(get_conf_value(conf, "PORT"));
	court.height = atoi(get_conf_value(conf, "LINES"));
	court.width = atoi(get_conf_value(conf, "COLS"));
	
	court.start.x = 3;
	court.start.y = 2;

	initfootball();
	
	
	if ((listener = socket_create_udp(port)) < 0) {
		perror(("server_socket_udp()"));
		exit(1);
	}

	epollfd = epoll_create(1);
	repollfd = epoll_create(1);
	bepollfd = epoll_create(1);

	//安全判断
	if (epollfd < 0 || repollfd < 0 || bepollfd < 0) {
		perror("epoll_create()");
		exit(1);
	}

	struct task_queue redQueue;
	struct task_queue blueQueue;
	
	task_queue_init(&redQueue, MAX, repollfd);
	task_queue_init(&blueQueue, MAX, bepollfd);

	pthread_create(&red_t, NULL, sub_reactor, (void *)&redQueue );
	pthread_create(&blue_t, NULL, sub_reactor, (void *)&blueQueue );
	//pthread_create(&heart_t, NULL, heart_beat, NULL);


	struct epoll_event ev, events[MAX];
	ev.events = EPOLLIN;
	ev.data.fd = listener;

	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener, &ev) < 0) {
		perror("server_epoll_ctl()");
		exit(1);
	}

	//signal(14, redraw);
	struct itimerval itimer;
	itimer.it_interval.tv_sec = 0;
	itimer.it_interval.tv_usec = 100000;
	itimer.it_value.tv_sec = 2;
	itimer.it_value.tv_usec = 0;

	setitimer(ITIMER_REAL, &itimer, NULL);


	while (1) {
		int nfds = epoll_wait(epollfd, events, MAX, -1);
		if (nfds < 0) {
			perror("server_epoll_wait()");
			exit(1);
		}
		for (int i = 0; i < nfds; i++) {
			struct User user;
			bzero(&user, sizeof(user));
			int new_fd = udp_accept(listener, &user);
				if (new_fd < 0) {
					printf("New Connection!\n");
					//可用多线程，持续接受数据试试，如果需要的话，请参考我们上课的程序
				}
		}
	}
	return 0;

}
