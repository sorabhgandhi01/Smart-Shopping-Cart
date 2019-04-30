#include <stdio.h>
#include <stdlib.h>
#include "led.h"

void onboardLED0(int signal)
{
	FILE* fd;

	fd = fopen("/sys/devices/platform/leds/leds/beaglebone:green:usr0/brightness", "w");
	fprintf(fd, "%i", signal);

	fclose(fd);
}


void onboardLED1(int signal)
{
        FILE* fd;

        fd = fopen("/sys/devices/platform/leds/leds/beaglebone:green:usr1/brightness", "w");
        fprintf(fd, "%i", signal);

        fclose(fd);
}


void onboardLED2(int signal)
{
        FILE* fd;

        fd = fopen("/sys/devices/platform/leds/leds/beaglebone:green:usr2/brightness", "w");
        fprintf(fd, "%i", signal);

        fclose(fd);
}


void onboardLED3(int signal)
{
        FILE* fd;

        fd = fopen("/sys/devices/platform/leds/leds/beaglebone:green:usr3/brightness", "w");
        fprintf(fd, "%i", signal);

        fclose(fd);
}
