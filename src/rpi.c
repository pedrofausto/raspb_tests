/*
 * rpi.c
 *
 *  Created on: 08/09/2014
 *      Author: pedro
 */

#include "RPInterface.h"

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

	INP_GPIO(14);
	OUT_GPIO(14);

	while(1)
	{
		sleep(1);
		GPIO_CLR = 1 << 14;
	}


}
