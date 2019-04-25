#ifndef POSIX_TIMER_H_
#define POSIX_TIMER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

#define HB_FREQ (5)

timer_t hb_send_id, hb_recv_id;

uint8_t FLAG_HB_SEND;
uint8_t FLAG_HB_RECV;

int set_timer(timer_t *handle, void (*handler)(union sigval));
int start_timer(timer_t handle, uint32_t interval_sec);
int stop_timer(timer_t handle);

void heart_beat_send_timer_handler(union sigval val);
void heart_beat_recv_timer_handler(union sigval val);

#endif
