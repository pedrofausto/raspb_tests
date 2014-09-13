/*
 * RPInterface.h
 *
 *  Created on: 05/09/2014
 *      Author: pedro
 *      Define macros that will be used to access virtual address,
 *      then configure and access GPIOs
 */

#ifndef RPINTERFACE_H_
#define RPINTERFACE_H_

#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>


/*
 * GPIO controller base address 0x20000000
 * Each GPIO will be accessed based on address offset
 */
#define BCM2708_PERI_BASE       0x20000000
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000)

#define BLOCK_SIZE 				(4*1024)


// Input/Output Access
struct bcm2835_peripheral {
    unsigned long addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
};

extern struct bcm2835_peripheral gpio;

/*
 * GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x)
 */
#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET  *(gpio.addr + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR  *(gpio.addr + 10) // clears bits which are 1 ignores bits which are 0

#define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))

int map_peripheral (struct bcm2835_peripheral *pointer);
void unmap_peripheral(struct bcm2835_peripheral *pointer);

#endif /* RPINTERFACE_H_ */
