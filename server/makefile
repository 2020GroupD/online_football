all : server.c ../common/common.c ../common/udp_epoll.c ../common/ball_status.c \
	../common/sub_reactor.c ../common/thread_pool.c ../common/game_ui.c \
	../common/heart_beat.h ../common/server_re_draw.c
	gcc server.c ../common/common.c ../common/udp_epoll.c ../common/sub_reactor.c \
		../common/thread_pool.c  ../common/game_ui.c ../common/ball_status.c \
		../common/heart_beat.c ../common/server_re_draw.c \
		-I ../common/ -lncurses -lpthread -lm
