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
#include "task_processor.h"


void *task_processor_thread(void *arg)
{
	TIVA_MSG r_msg;
	
	while (1)
	{
		if ((mq_receive(reciever_queue_t.mq, (char *)&r_msg, sizeof(r_msg), 0)) == -1) {
			printf("Message Recieve error");
		}
		
		printf("%x \t %x \t %d\n", r_msg.msg_type, r_msg.log_level, r_msg.sensor_data);
	}
}