/*
 * main.c
 *
 *  Created on: 16.07.2012
 *      Author: koprek_w
 */

#include <stdio.h>
#include "xil_cache.h"
#include "system.h"

struct structSystem bpm_fpga;

void enable_caches() {

    //Xil_ICacheEnableRegion(0x00000003);
    //Xil_DCacheEnableRegion(0x00000003);
    Xil_ICacheEnableRegion(0x00000003);
    Xil_DCacheEnableRegion(0x00000003);

    return;
}

int main() {


	enable_caches();
	structSystem_new(&bpm_fpga);
	bpm_fpga.init_hardware(&bpm_fpga);

	while(1)
		asm("nop");

	return 0;
}
