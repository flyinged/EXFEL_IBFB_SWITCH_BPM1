/*
 * func_ctrl_v1_01_a.c
 *
 *  Created on: 05.07.2012
 *      Author: koprek_w
 */

#include "func_ctrl_v1_01_a.h"

void func_ctrl_intr_mask(struct structFunctionController *this, unsigned char mask_state) {

	this->funcRegs->ctrl_status = mask_state;

	return;
}

void func_ctrl_intr_enable(struct structFunctionController *this) {
	func_ctrl_intr_mask(this, FUNC_CTRL_UNMAKS_INTR );
	return;
}

void func_ctrl_intr_disable(struct structFunctionController *this) {
	func_ctrl_intr_mask(this, FUNC_CTRL_MAKS_INTR);
	return;
}

void func_ctrl_init_interrupts(struct structFunctionController *this, unsigned int num_of_int_regs) {

	unsigned int i;

	/* enable interrupt on first memory cells */
	for (i=0;i<num_of_int_regs;i++)
		*(this->funcMemory+this->memSize+i) = FUNC_CTRL_INT_ENA;

		//adc12fl->funcMemory->func_int_ena[i] = ADC12FL_FUNC_CTRL_INT_ENA;

	return;
}

void func_intr_handler(struct structFunctionController *this) {

	while ((this->funcRegs->ctrl_status & FUNC_FIFO_EMPTY_MASK) == 0)
		if ((this->userCallback != NULL) && (this->userObject != NULL))
			this->userCallback(this->userObject, this->funcRegs->fifo_out);

	return;
}

int structFunctionController_new(struct structFunctionController *this, unsigned int base_addr_reg, unsigned int base_addr_mem, unsigned int memSize) {

	this->funcRegs = (struct structFunctionRegisters *)base_addr_reg;
	this->funcMemory = (volatile unsigned int *)base_addr_mem;
	this->memSize = memSize;
	//methods
	this->interruptHandler = func_intr_handler;
	this->interruptInit = func_ctrl_init_interrupts;
	this->interuptEnable = func_ctrl_intr_enable;
	this->interuptDisable = func_ctrl_intr_disable;

	return 0;
}
