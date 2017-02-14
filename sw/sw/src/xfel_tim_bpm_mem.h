/*
 * xfel_tim_bpm_mem.h
 *
 *  Created on: 10.11.2016
 *      Author: koprek_w
 */


#ifndef XFEL_TIM_BPM_MEM_H_
#define XFEL_TIM_BPM_MEM_H_

#include <stdio.h>


#define XFELTIM_CMD_TABLE				0x05
#define XFELTIM_CMD_SHOT_ID   			0x08

#define XFELTIM_IDENT_TRAIN1   			0x0B
#define XFELTIM_IDENT_TRAIN2   			0x0C
#define XFELTIM_IDENT_TRAIN3   			0x0D

struct structXFELTIMTrainParams {		//			   16 bytes
	unsigned int start;					// 	0x0000		4
	unsigned int duration;				// 	0x0004		4
	unsigned int increment;				// 	0x0008		4
	unsigned int bunches;				// 	0x000C		4
};

struct structXFELTIMParams {						//                 256 bytes
	struct structXFELTIMTrainParams trains[3];		// 0x0000		  	48
	unsigned int shotID;							// 0x0030			 4
	unsigned int invalidCmd;						// 0x0034			 4
	unsigned int invalidIdent;						// 0x0038			 4
	unsigned int invalidData;						// 0x003C			 4
	unsigned char pad256[192];						// 0x0040		   192
};

struct structXFELTIMRegs {
	volatile unsigned int rec_frames;
};

struct structXFELTIM {
	struct structXFELTIMRegs *regs;
	unsigned int *mem;
	struct structXFELTIMParams *timParams;
	int (*parse_frames)(struct structXFELTIM *this);
};

int structXFELTIM_new(struct structXFELTIM *this, unsigned int xfeltim_reg_addr, unsigned int xfeltim_mem_addr);


#endif /* XFEL_TIM_BPM_MEM_H_ */
