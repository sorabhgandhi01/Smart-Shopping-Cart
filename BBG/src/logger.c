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


const char *file_name = "log.txt";

void *logger_thread(void *arg)
{
	TIVA_MSG q_recv_msg;


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
			printf("Message Recieve error");
		}

		//printf("%x \t %x \t %d\n", q_recv_msg.msg_type, q_recv_msg.log_level, q_recv_msg.sensor_data);

		fptr = fopen(file_name, "a");

		if ((0 <= q_recv_msg.msg_type) && (q_recv_msg.msg_type <= REMOTE_NODE_OFF)) {
			 LOG_TO_FILE(fptr, "[MSG FROM TIVA] [%s] [%s]\r\n", LOG_LEVEL_STRING[q_recv_msg.log_level], \
                                                                                MSG_TYPE_STRING[q_recv_msg.msg_type]);
		}
		else if ((REMOTE_NODE_OFF < q_recv_msg.msg_type) && (q_recv_msg.msg_type <= RFID_SENSOR_DATA)) {
			LOG_TO_FILE(fptr, "[MSG FROM TIVA] [%s] [%s] Sensor data = %d\r\n", LOG_LEVEL_STRING[q_recv_msg.log_level], \
										MSG_TYPE_STRING[q_recv_msg.msg_type], \
										q_recv_msg.sensor_data);
		} else if (q_recv_msg.msg_type < 23) {
			LOG_TO_FILE(fptr, "[BBG]\t\t [%s] [%s]\r\n", LOG_LEVEL_STRING[q_recv_msg.log_level], \
										MSG_TYPE_STRING[q_recv_msg.msg_type]);
		}

		fclose(fptr);

		memset(&q_recv_msg, sizeof(q_recv_msg), 0);
	}
}
