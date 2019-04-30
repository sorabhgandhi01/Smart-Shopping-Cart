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
	TIVA_MSG send_msg;
	
	while (1)
	{
		if ((mq_receive(reciever_queue_t.mq, (char *)&r_msg, sizeof(r_msg), 0)) == -1) {
			printf("Message Recieve error");
		}
		
		//printf("%x \t %x \t %d\n", r_msg.msg_type, r_msg.log_level, r_msg.sensor_data);
		
		if (r_msg.msg_type == GESTURE_SENSOR_INACTIVE)
		{
			send_msg.msg_type = BBG_MOTOR_STOP_SIGNAL;
			send_msg.log_level = INFO;
			
			mq_send(logger_queue_t.mq, (char *) &send_msg, sizeof(send_msg), 0);
			mq_send(sender_queue_t.mq, (char *) &send_msg, sizeof(send_msg), 0); 
		}
		else if (r_msg.msg_type == DISTANCE_SENSOR_INACTIVE)
		{
			send_msg.msg_type = BBG_MOTOR_STOP_SIGNAL;
			send_msg.log_level = INFO;
			
			mq_send(logger_queue_t.mq, (char *) &send_msg, sizeof(send_msg), 0);
			mq_send(sender_queue_t.mq, (char *) &send_msg, sizeof(send_msg), 0);
		}
		else if (r_msg.msg_type == PUSH_BUTTON_SENSOR_DATA)
		{
			switch (r_msg.sensor_data)
			{
				case FORWARD_BUTTON_PRESSED:
					send_msg.msg_type = BBG_FORWARD_MOTION_SIGNAL;
					break;
				
				case FORWARD_BUTTON_RELEASED:
					send_msg.msg_type = BBG_MOTOR_STOP_SIGNAL;
					break;
				
				case BACKWARD_BUTTON_PRESSED:
					send_msg.msg_type = BBG_BACKWARD_MOTION_SIGNAL;
					break;
				
				case BACKWARD_BUTTON_RELEASED:
					send_msg.msg_type = BBG_MOTOR_STOP_SIGNAL;
					break;
				
				case LEFT_BUTTON_PRESSED:
					send_msg.msg_type = BBG_LEFT_MOTION_SIGNAL;
					break;
				
				case LEFT_BUTTON_RELEASED:
					send_msg.msg_type = BBG_MOTOR_STOP_SIGNAL;
					break;
				
				case RIGHT_BUTTON_PRESSED:
					send_msg.msg_type = BBG_RIGHT_MOTION_SIGNAL;
					break;
				
				case RIGHT_BUTTON_RELEASED:
					send_msg.msg_type = BBG_MOTOR_STOP_SIGNAL;
					break;
				
				default:
					send_msg.msg_type = BBG_MOTOR_STOP_SIGNAL;
					break;
			}
			
			send_msg.log_level = INFO;
			mq_send(logger_queue_t.mq, (char *) &send_msg, sizeof(send_msg), 0);
			mq_send(sender_queue_t.mq, (char *) &send_msg, sizeof(send_msg), 0); 
		}
		else if (r_msg.msg_type == DISTANCE_SENSOR_DATA)
		{
			if (r_msg.sensor_data <= 10)
			{
				send_msg.msg_type = BBG_MOTOR_STOP_SIGNAL;
				send_msg.log_level = INFO;
				mq_send(logger_queue_t.mq, (char *) &send_msg, sizeof(send_msg), 0);
				mq_send(sender_queue_t.mq, (char *) &send_msg, sizeof(send_msg), 0);
			} 
		}
		else if (r_msg.msg_type == GESTURE_SENSOR_DATA)
		{
			switch (r_msg.sensor_data)
			{
				case GS_FORWARD:
					send_msg.msg_type = BBG_FORWARD_MOTION_SIGNAL;
					break;				
				
				case GS_BACKWARD:
					send_msg.msg_type = BBG_BACKWARD_MOTION_SIGNAL;
					break;
				
				case GS_RIGHT:
					send_msg.msg_type = BBG_RIGHT_MOTION_SIGNAL;
					break;
				
				case GS_LEFT:
					send_msg.msg_type = BBG_LEFT_MOTION_SIGNAL;
					break;
				
				case GS_NO_GESTURE:
					send_msg.msg_type = BBG_MOTOR_STOP_SIGNAL;
					break;
				
				default:
					send_msg.msg_type = BBG_MOTOR_STOP_SIGNAL;
					break;
			}
			
			send_msg.log_level = INFO;
			mq_send(logger_queue_t.mq, (char *) &send_msg, sizeof(send_msg), 0);
			mq_send(sender_queue_t.mq, (char *) &send_msg, sizeof(send_msg), 0); 
		}
		else
		{
			
		}
		
	}
}
