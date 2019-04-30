#include "posix_timer.h"
#include "BBG_reciever.h"

int set_timer(timer_t *timer_id, void (*handler)(union sigval))
{
	struct 	sigevent sev;
	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = handler; 
	sev.sigev_notify_attributes = NULL;
	sev.sigev_value.sival_ptr = &timer_id;


	if (timer_create(CLOCK_REALTIME, &sev, timer_id) != 0) 
	{
		return -1;
	}

	return 0;
} 


int start_timer(timer_t timer_id, uint32_t interval_sec)
{
   struct itimerspec in;

    in.it_value.tv_sec = interval_sec;
    in.it_interval.tv_sec = interval_sec;

    if ((timer_settime(timer_id, 0, &in, NULL)) != 0)
    {
    	return -1;
    }

    return 0;
}


int stop_timer(timer_t timer_id)
{
    if ((timer_delete(timer_id)) != 0)
    {
    	printf("Error on delete timer function\n");
    	return -1;
    }

    return 0;
}


void heart_beat_send_timer_handler(union sigval val)
{
	FLAG_HB_SEND = 1;
	start_timer(hb_send_id, HB_FREQ);
}


void heart_beat_recv_timer_handler(union sigval val)
{
	FLAG_HB_RECV = 1;
	
	start_timer(hb_recv_id, HB_FREQ);
}
