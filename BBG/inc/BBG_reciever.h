
#ifndef _BBG_RECIEVER_H_
#define _BBG_RECIEVER_H_

//pthread_t thread[1];

void *uart_rx_thread(void *arg);

uint32_t current_count;
uint32_t previous_count;

#endif
