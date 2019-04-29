#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <stdint.h>

#include "comm_interface.h"
#include "queue.h"
#include "logger.h"

TIVA_MSG q_recv_msg;

const char *file_name = "log.txt";

void *logger_thread(void *arg)
{
	fptr = fopen(file_name, "r+");

	/* Remove file if it already exists */
    	if (fptr)
	    {
    		fclose(fptr);
    		remove(file_name);
    	}

	while(1)
	{
		if ((mq_receive(logger_queue_t.mq, (char *)&q_recv_msg, sizeof(q_recv_msg), 0)) == -1) {
			perror("Message Recieve error");
			exit(EXIT_FAILURE);
		}
	
		fptr = fopen(file_name, "a");

		LOG_TO_FILE("[MSG FROM TIVA]\t [%s] [%s] Sensor data = %d\r\n", LOG_LEVEL_STRING[q_recv_msg.log_level], \
										MSG_TYPE_STRING[q_recv_msg.msg_type], \
										q_recv_msg.sensor_data);

		fclose(fptr);
	}
}
