#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "BBG_sender.h"


void *uart_tx_thread(void *arg)
{
	int fd;
	int status = 1;
	char w_data = 0x7E;

	fd = uart_tx_open("/dev/ttyO4", 115200);
        if (fd != 0) {
                printf("Uart4 open failed\n");
		pthread_cancel(thread[0]);
        }

	if ((set_timer(&hb_send_id, heart_beat_send_timer_handler)) != 0)
	{
		printf("Error in setting-up timer for heat-beat send task\n");
	}

	if ((start_timer(hb_send_id, HB_FREQ)) != 0)
	{
		printf("Error in starting the timer for heart-beat send task\n");
	}

	while (1) 
	{
		if (FLAG_HB_SEND) {

			status = uart_write(&w_data, 1);
			FLAG_HB_SEND = 0;
		}
	}

	pthread_cancel(thread[0]);
}
