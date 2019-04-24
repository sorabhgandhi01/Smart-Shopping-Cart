# _*_ Makefile _*_

CC = arm-linux-gnueabihf-gcc

CFLAGS = -Iinc/

LIBS = -lpthread

vpath %.c src/
vpath %.h inc/

SRC := uart.c main.c

OBJ := $(SRC:.c=.o)

control_node: $(OBJ)
	$(CC) -o control_node $(OBJ) $(CFLAGS) $(LIBS)

clean:
	rm -f *.o control_node
