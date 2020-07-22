all : server.c ../common/common.c ../common/udp_epoll.c \
	../common/sub_reactor.c ../common/thread_pool.c 
	gcc server.c ../common/common.c ../common/udp_epoll.c ../common/sub_reactor.c \
		../common/thread_pool.c  \
		-I ../common/ -lncurses -lpthread
