/*
 * interrupt.h
 *
 *  Created on: 16.07.2012
 *      Author: koprek_w
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <stdlib.h>
#include "xparameters.h"
#include "xil_exception.h"
#include "xintc_l.h"
//#include "system.h"

#define XREG_MSR_FLOATING_POINT_UNIT_ENABLE  0x00002000

struct structInterruptRegs {
	volatile unsigned int isr;			// XIN_ISR_OFFSET      0	/* Interrupt Status Register */
	volatile unsigned int ipr;			// XIN_IPR_OFFSET      4	/* Interrupt Pending Register */
	volatile unsigned int ier;			// XIN_IER_OFFSET      8	/* Interrupt Enable Register */
	volatile unsigned int iar;			// XIN_IAR_OFFSET      12	/* Interrupt Acknowledge Register */
	volatile unsigned int sie;			// XIN_SIE_OFFSET      16	/* Set Interrupt Enable Register */
	volatile unsigned int cie;			// XIN_CIE_OFFSET      20	/* Clear Interrupt Enable Register */
	volatile unsigned int ivr;			// XIN_IVR_OFFSET      24	/* Interrupt Vector Register */
	volatile unsigned int mer;			// XIN_MER_OFFSET      28	/* Master Enable Register */
	volatile unsigned int imr;			// XIN_IMR_OFFSET      32	/* Interrupt Mode Register , this is present */
};

struct structInterrupt {
	struct structInterruptRegs *deviceRegs;
	struct structSystem *sys;
	void (*init)(struct structInterrupt *);
	void (*enableInterrupts) ();
	void (*disableInterrupts) ();
	void (*interruptHandlers[XPAR_INTC_MAX_NUM_INTR_INPUTS]) ();		// callback function for interrupt handlers
	void *interruptObjects[XPAR_INTC_MAX_NUM_INTR_INPUTS];				// callback objects passed as an argument for the interrupt handler
	void (*assign_handler)(struct structInterrupt *this, unsigned int interrupt, void *object, void *function);
};

int structInterrupt_new(struct structInterrupt *this, unsigned int base_addr, struct structSystem *sys);


#endif /* INTERRUPT_H_ */
