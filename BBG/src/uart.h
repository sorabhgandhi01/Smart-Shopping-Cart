
#ifndef _UART_H_
#define _UART_H_

struct comm_serial {
	int fd;
	unsigned int baudrate;
	char device_name[40];
};

static struct comm_serial rx;
static struct comm_serial tx;

#define BAUDRATE(b)     case b: baud = B ## b; break

int uart_rx_open(const char *device_name, unsigned int baudrate);
int uart_tx_open(const char *device_name, unsigned int baudrate);

ssize_t uart_read(void *buf, size_t count);
ssize_t uart_write(char *buf, size_t count);

int uart_rx_close(void);
int uart_tx_close(void);

#endif
