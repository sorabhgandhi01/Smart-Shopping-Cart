# _*_ Makefile _*_

CC = arm-linux-gnueabihf-gcc

CFLAGS = -Iinc/ \
	 -g

LIBS = -lpthread -lrt

vpath %.c src/
vpath %.h inc/

SRC := uart.c main.c posix_timer.c logger.c BBG_sender.c BBG_reciever.c queue.c task_processor.c

OBJ := $(SRC:.c=.o)

control_node: $(OBJ)
	$(CC) -o control_node $(OBJ) $(CFLAGS) $(LIBS)

clean:
	rm -f *.o control_node
