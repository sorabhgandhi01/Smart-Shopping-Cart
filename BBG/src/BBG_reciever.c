#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/syscall.h>

#include "uart.h"
#include "comm_interface.h"
#include "posix_timer.h"
#include "BBG_reciever.h"
#include "queue.h"

void *uart_rx_thread(void *arg)
{
	int fd;
    int status = 1;
	TIVA_MSG r_data;

        fd = uart_rx_open("/dev/ttyO1", 115200);
        if (fd != 0) {
                printf("Uart4 open failed\n");
                pthread_cancel(thread[1]);
        }

	printf("Rx task initialized\r\n");

        while (1)
        {
			r_data.msg_type = 0;
			status = uart_read(&r_data, sizeof(r_data));

			if (status > 0) {
				printf("REC %x \t %x \t %d\n", r_data.msg_type, r_data.log_level, r_data.sensor_data);
			
				if ((mq_send(logger_queue_t.mq, (char *) &r_data, sizeof(r_data), 0)) == -1) {
					printf("Uart_rx_thread: Message send error");
				}
				
				if ((mq_send(reciever_queue_t.mq, (char *) &r_data, sizeof(r_data), 0)) == -1) {
					printf("Uart_rx_thread: Message send error");
				}
			}
        }

        pthread_cancel(thread[1]);
}
