#include "head.h"

int port;
char *conf = "./footballd.conf";
char ans[255];
int bepollfd, repollfd;
struct User *rteam, *bteam;
struct Map court;
struct Bpoint ball;
struct BallStatus ball_status;

WINDOW *Football, *Football_t, *Message, *Help, *Score, *Write;
pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv) {
    int opt, listener, epollfd;
    pthread_t red_t, blue_ti, heart_t;
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

    bzero(&court,sizeof(court));
    bzero(&ball,sizeof(ball));
    bzero(&ball_status,sizeof(ball_status));

    //判断一配置文件合法性,如果不做合法性判断，在下面一行代码中，会很容易出现段错误，为什么呢？
    if (!port) port = atoi(get_conf_value(conf, "PORT"));
    court.width=atoi(get_conf_value(conf,"COLS"));
    court.height=atoi(get_conf_value(conf,"LINES"));
    court.start.x=3;
    court.start.y=2;
    
    initfootball();



    if ((listener = socket_create_udp(port)) < 0) {
        perror("socket_create_udp()");
        exit(1);
    }
    
    epollfd = epoll_create(1);
    repollfd = epoll_create(1);
    bepollfd = epoll_create(1);
    //安全判断
    if(epollfd < 0 || repollfd < 0 || bepollfd < 0){
        perror("epoll_create()");
        exit(1);
    }
    

    rteam=(struct User*)calloc(MAX, sizeof(struct User));
    bteam=(struct User*)calloc(MAX, sizeof(struct User));
    
    struct task_queue redQueue;
    struct task_queue blueQueue;

    task_queue_init(&redQueue, MAX, repollfd);
    task_queue_init(&blueQueue, MAX, bepollfd);

    pthread_create(&red_t, NULL, sub_reactor, (void*)&redQueue);
    pthread_create(&blue_t, NULL, sub_reactor, (void*)&blueQueue);
    pthread_create(&heart_t,NULL,hear_beat,NULL);

//    printf("ppp\n");
    struct epoll_event ev, events[MAX];
    ev.events = EPOLLIN;
    ev.data.fd = listener;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener, &ev) < 0) {
        perror("epoll_ctl");
        exit(1);
    }
    
    signal(SIGALRM, re_draw);
    struct itimeval itimer;
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = 100000;
    itimer.it_value.tv_sec = 2;
    itimer.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &itimer, NULL);

    while (1) {
    //    printf("wait before\n");
        int nfds = epoll_wait(epollfd, events, MAX, -1);
      //  printf("wait end\n");
        if (nfds < 0) {
            perror("epoll_wait()");
            exit(1);
        }
        for (int i = 0; i < nfds; i++) {
            struct User user;
            bzero(&user, sizeof(user));
            if (events[i].data.fd == listener) {
//                printf("...\n");
                int new_fd = udp_accept(listener, &user);
  //              printf("%d\n",new_fd);
                if (new_fd > 0) {
                    printf("New Connection!\n");
                    //可用多线程，持续接受数据试试，如果需要的话，请参考我们上课写的程序
                    add_to_sub_reactor(&user);
        //            printf("end\n");
                }
            }
        }
    }

    return 0;
}

