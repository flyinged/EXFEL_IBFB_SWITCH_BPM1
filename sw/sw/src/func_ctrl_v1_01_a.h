/*
 * func_ctrl_v1_01_a.h
 *
 *  Created on: 05.07.2012
 *      Author: koprek_w
 */

#ifndef FUNC_CTRL_V1_01_A_H_
#define FUNC_CTRL_V1_01_A_H_

#include <stdlib.h>

#define FUNC_FIFO_EMPTY_MASK				0x02
#define FUNC_CTRL_MAKS_INTR					0x00000004
#define FUNC_CTRL_UNMAKS_INTR				0x00000000
#define FUNC_CTRL_INT_ENA					0x00000001


struct structFunctionRegisters {
	volatile unsigned int fifo_out			;					// 0x00
	volatile unsigned int ctrl_status		;					// 0x04
};

struct structFunctionController {
	struct structFunctionRegisters *funcRegs;
	volatile unsigned int *funcMemory;
	unsigned int memSize;
	void (*interruptInit)();
	void (*interuptDisable)();
	void (*interuptEnable)();
	void (*interruptHandler) ();
	void (*userCallback)(void *funcUserObject, unsigned int function);
	void *userObject;
};

int structFunctionController_new(struct structFunctionController *this, unsigned int base_addr_reg, unsigned int base_addr_mem, unsigned int memSize);


#endif /* FUNC_CTRL_V1_01_A_H_ */
