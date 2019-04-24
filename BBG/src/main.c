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

	while (status > 0) 
	{
		status = uart_write(&w_data, 1);

		usleep(200000);
	}

	pthread_cancel(thread[0]);
}

void *uart_rx_thread(void *arg)
{
	int fd;
        int status = 1;
	char r_data;

        fd = uart_rx_open("/dev/ttyO1", 115200);
        if (fd != 0) {
                printf("Uart4 open failed\n");
                pthread_cancel(thread[1]);
        }

        while (1)
        {
                status = uart_read(&r_data, 1);

                if (status > 0) {
			printf("Read data = %x\n", r_data);
		}
        }

        pthread_cancel(thread[1]);
}
