#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <termios.h> 
#include <errno.h> 
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

#include "uart.h"

int uart_rx_open(const char *device_name, unsigned int baudrate) {
	
	struct termios termios;
	unsigned int baud = 0;
	rx.fd = -1;
	
	if (!device_name) {
		printf("%s: invalid device name '%s'; return -EINVAL\n",
		       __func__, device_name);
		return -EINVAL;
	}
	
	switch (baudrate) {
		BAUDRATE(0);
		BAUDRATE(9600);
		BAUDRATE(19200);
		BAUDRATE(38400);
		BAUDRATE(57600);
		BAUDRATE(115200);
		default:
			printf("%s: invalid baudrate %d; return -EINVAL\n",
		       __func__, baudrate);
			return -EINVAL;
	}
	
	strncpy(rx.device_name, device_name, 40);
	rx.baudrate = baudrate;
	
	rx.fd = open(device_name, O_RDWR | O_NOCTTY);
	if (rx.fd < 0) {
		printf("%s: open('%s') failed (errno=%d)\n",
		       __func__, device_name, errno);
		return -1;
	}
	
	tcgetattr(rx.fd, &termios);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 5;
	termios.c_cflag = baud | CS8 | CLOCAL | CREAD;
	termios.c_iflag = 0;
	termios.c_oflag &= ~(OPOST);
	termios.c_lflag &= ~(ECHO | ICANON | ISIG | ECHOE | ECHOK | ECHONL);
	
	tcflush(rx.fd, TCIFLUSH);
	tcsetattr(rx.fd, TCSANOW, &termios);

	return 0;
}


int uart_tx_open(const char *device_name, unsigned int baudrate) {

        struct termios termios;
        unsigned int baud = 0;
        tx.fd = -1;

        if (!device_name) {
                printf("%s: invalid device name '%s'; return -EINVAL\n",
                       __func__, device_name);
                return -EINVAL;
        }

        switch (baudrate) {
                BAUDRATE(0);
                BAUDRATE(9600);
                BAUDRATE(19200);
                BAUDRATE(38400);
                BAUDRATE(57600);
                BAUDRATE(115200);
                default:
                        printf("%s: invalid baudrate %d; return -EINVAL\n",
                       __func__, baudrate);
                        return -EINVAL;
        }

	strncpy(tx.device_name, device_name, 40);
        tx.baudrate = baudrate;

        tx.fd = open(device_name, O_RDWR | O_NOCTTY);
        if (tx.fd < 0) {
                printf("%s: open('%s') failed (errno=%d)\n",
                       __func__, device_name, errno);
                return -1;
        }

        tcgetattr(tx.fd, &termios);
        termios.c_cc[VMIN] = 1;
        termios.c_cc[VTIME] = 5;
        termios.c_cflag = baud | CS8 | CLOCAL | CREAD;
        termios.c_iflag = 0;
        termios.c_oflag &= ~(OPOST);
        termios.c_lflag &= ~(ECHO | ICANON | ISIG | ECHOE | ECHOK | ECHONL);

        tcflush(tx.fd, TCIFLUSH);
	tcsetattr(tx.fd, TCSANOW, &termios);

	return 0;
}


ssize_t uart_read(void *buf, size_t count) {
	
	ssize_t bytes_read;
	
	if (!buf || count < 0) {
		printf("%s: bufr=%p, count=%d; return -EINVAL\n",
		       __func__, buf, count);
		return -EINVAL;
	}
	
	bytes_read = read(rx.fd, buf, count);
	if (bytes_read < 0 && errno == EAGAIN)
		return 0;
	if (bytes_read < 0) {
		printf("%s: error=%d trying to read %d bytes\n", __func__,
		       errno, count);
		return -errno;
	}
	
	return bytes_read;
}


ssize_t uart_write(char *buf, size_t count) {
	
	ssize_t bytes_written;
	
	if (!buf || count < 0) {
		printf("%s: bufr=%p, count=%d; return -EINVAL\n",
		       __func__, buf, count);
		return -EINVAL;
	}
	
	bytes_written = write(tx.fd, buf, count);
	
	if (bytes_written < 0) {
		printf("%s: error=%d trying to write %d bytes\n",
		       __func__, errno, count);
		return -errno;
	} else {
		printf("Wriiten data = %c of length %x\n", *buf, count);
	}
	
	return bytes_written;
}


int uart_rx_close(void) {
	
	if (close(rx.fd) == -1) {
		printf("%s: close(%d) failed (errno=%d)\n", __func__,
		       rx.fd, errno);
		return -1;
	}
	
	rx.fd = -1;
	
	return 0;
}


int uart_tx_close(void) {

        if (close(tx.fd) == -1) {
                printf("%s: close(%d) failed (errno=%d)\n", __func__,
                       tx.fd, errno);
                return -1;
        }

        tx.fd = -1;

        return 0;
}

