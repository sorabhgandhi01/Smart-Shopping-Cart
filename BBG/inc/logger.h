
#ifndef _LOGGER_QUEUE_H
#define _LOGGER_QUEUE_H

#define LOG_TO_FILE(fp, format, ...) \
do{ \
	fprintf(fp, format, ##__VA_ARGS__); \
	fflush(fp); \
}while(0)

FILE *fptr;

void *logger_thread(void *arg);

#endif
