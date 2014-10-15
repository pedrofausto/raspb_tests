/*
 * rpi.c
 *
 *  Created on: 08/09/2014
 *      Author: pedro
 */

#include "RPInterface.h"
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>

unsigned int time = 0;

int main (int argc, char* argv[])
{
	if(map_peripheral(&gpio) == -1)
	{
		perror("Failed to map the physical GPIO registers into virtual memory.\n");
		return -1;
	}



/*
 * Defining pin 8 as output.
 * This means that we need to change the registers that belongs to GPIO 14
 */

	configInput(23);
	configOutput(23);

	configInput(24);

	while(1)
	{
		sleep(1);
		setOutput(23);
		printf("Pin 23: %c\n", readPin(23));
		sleep(1);
		printf("Pin 24: %c\n", readPin(24));
	}

}
