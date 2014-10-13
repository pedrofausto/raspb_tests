/*
 ============================================================================
 Name        : RPInterface.c
 Author      : Pedro Fausto
 Version     :
 Copyright   : GPL v2
 Description : Raspberry GPIO access example, Ansi-style
 ============================================================================
 */

#include "RPInterface.h"

struct bcm2835_peripheral gpio = {GPIO_BASE};

/*
 * Access to the peripheral
 */
int map_peripheral (struct bcm2835_peripheral *pointer)
{
	// pointing to file descriptor
	pointer->mem_fd = open("/dev/mem", O_RDWR | O_SYNC);

	if(pointer == NULL)
	{
		perror("Couldn't open the device /dev/mem. Please, try checking your permissions\n");
		return	-1;
	}

	pointer->map = mmap(
		NULL,
		BLOCK_SIZE,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		pointer->mem_fd,
		pointer->addr_p
	);

	if (pointer->map == MAP_FAILED)
	{
		perror("mmap error.\n");
		return	-1;
	}

	pointer->addr = (volatile unsigned int *)pointer->map;

	return 0;
}

void unmap_peripheral(struct bcm2835_peripheral *pointer)
{
	munmap(pointer->map, BLOCK_SIZE);
	close(pointer->mem_fd);
}

int configInput(int gpioNumber)
{
	assert(gpioNumber <= 40 || gpioNumber >= 1);

	if((INP_GPIO(gpioNumber)))
		return 0;
	else
	{
		printf("Failed to set GPIO %d as input.\n", gpioNumber);
		return -1;
	}
}

int configOutput(int gpioNumber)
{
	assert(gpioNumber <= 40 || gpioNumber >= 1);

	if((OUT_GPIO(gpioNumber)))
		return 0;
	else
	{
		printf("Failed to set GPIO %d as output.\n", gpioNumber);
		return -1;
	}
}

void setOutput(int gpioNumber)
{
	assert(gpioNumber <= 40 || gpioNumber >= 1);
	GPIO_SET = 1 << gpioNumber;
}

void clearOutput(int gpioNumber)
{
	assert(gpioNumber <= 40 || gpioNumber >= 1);
	GPIO_CLR = 1 << gpioNumber;
}

int readInput(int gpioNumber)
{
	assert(gpioNumber <= 40 || gpioNumber >= 1);
	return GPIO_READ(gpioNumber);
}
