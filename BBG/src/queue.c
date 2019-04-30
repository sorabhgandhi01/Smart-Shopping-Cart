
#include "queue.h"
#include "comm_interface.h"

uint8_t logger_queue_open(void)
{
    size_t size = sizeof(TIVA_MSG);

    //First we need to set up the attribute structure
    logger_queue_t.attr.mq_maxmsg = MAX_SIZE;
    logger_queue_t.attr.mq_msgsize = size;
    logger_queue_t.attr.mq_flags = 0;
    logger_queue_t.attr.mq_curmsgs = 5;
	
    logger_queue_t.mq = mq_open(logger_queue_name, O_CREAT | O_RDWR, 0666, &(logger_queue_t.attr));
    if (logger_queue_t.mq == (mqd_t) -1) {

        perror("Logger Queue Open Error");
        return -1;
    }
	
	return 0;
}



uint8_t sender_queue_open(void)
{
    size_t size = sizeof(TIVA_MSG);

    //First we need to set up the attribute structure
    sender_queue_t.attr.mq_maxmsg = MAX_SIZE;
    sender_queue_t.attr.mq_msgsize = size;
    sender_queue_t.attr.mq_flags = 0;
    sender_queue_t.attr.mq_curmsgs = 5;
	
    sender_queue_t.mq = mq_open(sender_queue_name, O_CREAT | O_RDWR | O_NONBLOCK, 0666, &(sender_queue_t.attr));
    if (sender_queue_t.mq == (mqd_t) -1) {

        printf("Sender Queue Open Error");
        return -1;
    }
	
	return 0;	
}



uint8_t reciever_queue_open(void)
{
    size_t size = sizeof(TIVA_MSG);

    //First we need to set up the attribute structure
    reciever_queue_t.attr.mq_maxmsg = MAX_SIZE;
    reciever_queue_t.attr.mq_msgsize = size;
    reciever_queue_t.attr.mq_flags = 0;
    reciever_queue_t.attr.mq_curmsgs = 5;
	
    reciever_queue_t.mq = mq_open(reciever_queue_name, O_CREAT | O_RDWR, 0666, &(reciever_queue_t.attr));
    if (reciever_queue_t.mq == (mqd_t) -1) {

        perror("Reciever Queue Open Error");
        return -1;
    }
	
	return 0;	
}
