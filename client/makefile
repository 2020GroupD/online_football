all : client.c ../common/common.c ../common/udp_epoll.c ../common/ball_status.c \
	../common/sub_reactor.c ../common/thread_pool.c ../common/game_ui.c \
	../common/heart_beat.h ../common/server_re_draw.c ../common/show_data_stream.c
	gcc client.c ../common/common.c ../common/udp_epoll.c \
		../common/game_ui.c  \
        ../common/show_data_stream.c ../common/show_strength.c \
        ../common/client_recv.c ../common/send_chat.c ../common/send_ctl.c \
		-I ../common/ -lncurses -lpthread -lm
