/*
	queue.h

*/

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

#define logger_queue_name "/logger_queue"
#define sender_queue_name "/sender_queue"
#define reciever_queue_name "/reciever_queue"

#define MAX_SIZE 10

typedef struct queue_t
{
	mqd_t mq;
	struct mq_attr attr;
}queue_handle;

queue_handle logger_queue_t;
queue_handle sender_queue_t;
queue_handle reciever_queue_t;

uint8_t logger_queue_open(void);
uint8_t sender_queue_open(void);
uint8_t reciever_queue_open(void);


#endif
