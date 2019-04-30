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
#include "task_processor.h"

void task_queue_open();

void handle_sigint(int sig)
{
    uart_rx_close();
    uart_tx_close();
    mq_close(logger_queue_t.mq);
    mq_unlink(logger_queue_name);
    mq_close(sender_queue_t.mq);
    mq_unlink(sender_queue_name);
    mq_close(reciever_queue_t.mq);
    mq_unlink(reciever_queue_name);

    fclose(fptr);
    pthread_cancel(thread[0]);
    pthread_cancel(thread[1]);
    pthread_cancel(thread[2]);
    pthread_cancel(thread[3]);
    exit(0);
}

int main()
{
	int rc = 0;
	TIVA_MSG q_msg;

	logger_queue_open();
	reciever_queue_open();
	sender_queue_open();
	
#if 0
	if ((logger_queue_open() == 0) && (reciever_queue_open() == 0) && (sender_queue_open() == 0))
	{
		printf("[BBG] [DEBUG] Queue Open Start-up Test Passed Successfully\r\n");
		/*
		q_msg.msg_type = BBG_QUEUE_START_UP_TEST_PASSED;
		q_msg.log_level = DEBUG;
		if ((mq_send(logger_queue_t.mq, (char *) &q_msg, sizeof(q_msg), 0)) == -1) {
			printf("[BBG] [ERROR] Failed to send the Queue startup test status to Logger\r\n");
		}*/
	} else {
		printf("[BBG] [Error] Failed to Create Message Queue\r\n");
		exit(0);
	}
#endif		

	if (((rc = pthread_create(&thread[0], NULL, uart_tx_thread, NULL)) != 0))
	{

	}
	if ((rc = pthread_create(&thread[1], NULL, uart_rx_thread, NULL)) != 0)
	{

	}

	if ((rc = pthread_create(&thread[2], NULL, logger_thread, NULL)) != 0)
	{
	
	}	
	
	if ((rc = pthread_create(&thread[3], NULL, task_processor_thread, NULL)) != 0)
	{

	}

#if 0
		printf("[BBG] [Error] Failed to Create Thread\r\n");
		
		/*q_msg.msg_type = BBG_TC_START_UP_TEST_FAILED;
		q_msg.log_level = ERROR;
		if ((mq_send(logger_queue_t.mq, (char *) &q_msg, sizeof(q_msg), 0)) == -1) {
			printf("[BBG] [ERROR] Failed to send the Thread Creation startup test status to Logger\r\n");
		}*/
		
		exit(0);
	} else {
		printf("[BBG] [DEBUG] Thread Creation Start-up Test Passed Successfully\r\n");
		
		/*q_msg.msg_type = BBG_TC_START_UP_TEST_PASSED;
		q_msg.log_level = DEBUG;
		if ((mq_send(logger_queue_t.mq, (char *) &q_msg, sizeof(q_msg), 0)) == -1) {
			printf("[BBG] [ERROR] Failed to send the Thread Creation startup test status to Logger\r\n");
		}*/
	}
#endif
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
	pthread_join(thread[3], NULL);

	return 0;
}
	
	
