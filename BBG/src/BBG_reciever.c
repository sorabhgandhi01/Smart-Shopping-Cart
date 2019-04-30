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
#include <sys/select.h>

#include "uart.h"
#include "comm_interface.h"
#include "posix_timer.h"
#include "BBG_reciever.h"
#include "queue.h"

void *uart_rx_thread(void *arg)
{
	int fd;
        int status = 1;

	fd_set set;
	struct timeval timeout;

	//uint32_t current_count = 0;
	//uint32_t previous_count = 1;

	TIVA_MSG r_data;
	TIVA_MSG hb_send;

        fd = uart_rx_open("/dev/ttyO1", 115200);
        if (fd != 0) {
                printf("Uart4 open failed\n");
                pthread_cancel(thread[1]);
        }

#if 0
	FD_ZERO(&set); /* clear the set */
  	FD_SET(filedesc, &set); /* add our file descriptor to the set */

  	timeout.tv_sec = 0;
  	timeout.tv_usec = 1000;
#endif

	if ((set_timer(&hb_recv_id, heart_beat_recv_timer_handler)) != 0)
        {
                printf("Error in setting-up timer for heat-beat receive task\n");
        }

        if ((start_timer(hb_recv_id, HB_FREQ)) != 0)
        {
                printf("Error in starting the timer for heart-beat receive task\n");
        }

	

        while (1)
        {
			r_data.msg_type = 0;
			status = uart_read(&r_data, sizeof(r_data));


			if (status > 0) {
				//printf("REC %d \t %d \t %d\n", r_data.msg_type, r_data.log_level, r_data.sensor_data);
				printf("MSG FROM TIVA] [%s] [%s] data = %d\r\n", LOG_LEVEL_STRING[r_data.log_level], \
                                                                                MSG_TYPE_STRING[r_data.msg_type], \
                                                                                r_data.sensor_data);

				if (r_data.msg_type == HEART_BEAT) {
					current_count++;
				}
				else {
			
					if ((mq_send(logger_queue_t.mq, (char *) &r_data, sizeof(r_data), 0)) == -1) {
						printf("Uart_rx_thread: Message send error");
					}
				
					if ((mq_send(reciever_queue_t.mq, (char *) &r_data, sizeof(r_data), 0)) == -1) {
						printf("Uart_rx_thread: Message send error");
					}
				
				}
			}


			if (FLAG_HB_RECV) {

				if (current_count <= previous_count) {

					printf("Remote Node failed\n");
                                        hb_send.msg_type =  REMOTE_NODE_OFF;
                                        hb_send.log_level = ERROR;
                                        mq_send(logger_queue_t.mq, (char *) &hb_send, sizeof(hb_send), 0);

				} else {
					hb_send.msg_type = 0;
                                        hb_send.log_level = INFO;
                                        mq_send(logger_queue_t.mq, (char *) &hb_send, sizeof(hb_send), 0);
				}

				FLAG_HB_RECV = 0;
			}

        }

        pthread_cancel(thread[1]);
}
