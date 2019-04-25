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

#define NUM_THREAD 3

pthread_t thread[NUM_THREAD];

void *uart_tx_thread(void *arg);
void *uart_rx_thread(void *arg);

void handle_sigint(int sig)
{
        uart_rx_close();
	uart_tx_close();
	pthread_cancel(thread[0]);
	pthread_cancel(thread[1]);
        exit(0);
}

int main()
{
	int rc = 0;

	if ((rc = pthread_create(&thread[0], NULL, uart_tx_thread, NULL)) != 0)
	{
		perror("uart_tx_thread create:");
		exit(EXIT_FAILURE);
	}

	if ((rc = pthread_create(&thread[1], NULL, uart_rx_thread, NULL)) != 0)
	{
		perror("uart_rx_thread create:");
		exit(EXIT_FAILURE);
	}

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);

	return 0;
}

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

			uart_write(&w_data, 1);
			FLAG_HB_SEND = 0;
		}
	}

	pthread_cancel(thread[0]);

}

void *uart_rx_thread(void *arg)
{
	int fd;
        int status = 1;
	//char r_data;
	TIVA_MSG r_data;

        fd = uart_rx_open("/dev/ttyO1", 115200);
        if (fd != 0) {
                printf("Uart4 open failed\n");
                pthread_cancel(thread[1]);
        }

        while (1)
        {
		r_data.msg_type = 0;
                status = uart_read(&r_data, sizeof(r_data));

                if (status > 0) {
			printf("MSG_TYPE = %x Sensor_data = %x\n", r_data.msg_type, r_data.data.pb_data);
		}
        }

        pthread_cancel(thread[1]);
}
