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
#include <mqueue.h>
#include <sys/syscall.h>
#include <errno.h>

#include "uart.h"
#include "comm_interface.h"
#include "posix_timer.h"
#include "BBG_sender.h"
#include "BBG_reciever.h"
#include "queue.h"
#include "logger.h"

//#define NUM_THREAD 3
//pthread_t thread[NUM_THREAD];

void task_queue_open();

void handle_sigint(int sig)
{
    uart_rx_close();
    uart_tx_close();
    pthread_cancel(thread[0]);
    pthread_cancel(thread[1]);
    mq_close(logger_queue_t.mq);
    mq_unlink(logger_queue_name);
    exit(0);
}

int main()
{
	int rc = 0;
	
	task_queue_open();

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
	
	if ((rc = pthread_create(&thread[2], NULL, logger_thread, NULL)) != 0)
	{
		perror("logger_thread create:");
		exit(EXIT_FAILURE);
	}

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);

	return 0;
}


void task_queue_open()
{
    size_t size = sizeof(TIVA_MSG);

    //First we need to set up the attribute structure
    logger_queue_t.attr.mq_maxmsg = MAX_SIZE;
    logger_queue_t.attr.mq_msgsize = size;
    logger_queue_t.attr.mq_flags = 0;
    logger_queue_t.attr.mq_curmsgs = 5;
	
    logger_queue_t.mq = mq_open(logger_queue_name, O_CREAT | O_RDWR, 0666, &(logger_queue_t.attr));
    if (logger_queue_t.mq == (mqd_t) -1) {

        perror("Queue Open Error");
        exit(EXIT_FAILURE);
    }
}
	
	
