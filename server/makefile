all : server.c ../common/common.c ../common/udp_epoll.c \
	../common/sub_reactor.c ../common/thread_pool.c ../common/game_ui.c
	gcc server.c ../common/common.c ../common/udp_epoll.c ../common/sub_reactor.c \
		../common/thread_pool.c  ../common/game_ui.c \
		-I ../common/ -lncurses -lpthread
