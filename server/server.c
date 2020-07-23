#include "head.h"
int port;
char *conf = "./footballd.conf";
int bepollfd, repollfd;
char ans[512];
struct User *rteam, *bteam;
pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER;
struct Map court;
struct Bpoint ball;  //球的位置
struct BallStatus ball_status;
WINDOW *Football, *Football_t, *Message, *Help, *Score, *Write;

int main(int argc, char **argv) {
    int opt, listener, epollfd;
    pthread_t red_t, blue_t;

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
    
    //判断一配置文件合法性,如果不做合法性判断，在下面一行代码中，会很容易出现段错误，为什么呢？
    
    if (!port) port = atoi(get_conf_value(conf, "PORT"));
    court.width=atoi(get_conf_value(conf,"COLS"));
    court.height=atoi(get_conf_value(conf,"LINES"));
    court.start.x=3;
    court.start.y=2;
    ball.x = court.width / 2;
    ball.y = court.height / 2;
    
    initfootball();
        
    if ((listener = socket_create_udp(port)) < 0) {
        perror("socket_create_udp()");
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

    //创建队列
    rteam = (struct User *) calloc (MAX, sizeof(struct User));
    bteam = (struct User *) calloc (MAX, sizeof(struct User));

    struct task_queue redQueue;
    struct task_queue blueQueue;

    task_queue_init(&redQueue, MAX, repollfd);
    task_queue_init(&blueQueue, MAX, bepollfd);
    
    pthread_create(&red_t, NULL, sub_reactor, (void *)&redQueue );
    pthread_create(&blue_t, NULL, sub_reactor, (void *)&blueQueue );
    
    struct epoll_event ev, events[MAX];
    ev.events = EPOLLIN;
    ev.data.fd = listener;
    
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener, &ev) < 0) {
        perror("epoll_ctl");
        exit(1);
    } 
    while (1) {
        int nfds = epoll_wait(epollfd, events, MAX, -1);
        if (nfds < 0) {
            perror("epoll_wait()");
            exit(1);  
        }

        for (int i = 0; i < nfds; i++) {
            struct User user;
            bzero(&user, sizeof(user));
            if (events[i].data.fd == listener) {
                int new_fd = udp_accept(listener, &user);
                if (new_fd > 0) {
                    w_gotoxy_puts(Message, 0, 0, "New connection!\n");
                    //可用多线程，持续接受数据试试，如果需要的话，请参考我们上课写的程序
                    add_to_sub_reactor(&user);
                }       
            }                
        }        
    }
    return 0;
}

    
