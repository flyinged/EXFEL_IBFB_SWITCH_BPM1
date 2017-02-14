/*
 * gpac_qdr2_splb_v2_00_a.c
 *
 *  Created on: 10.07.2013
 *      Author: koprek_w
 */


#include "gpac_qdr2_splb_v2_00_a.h"


int qdr2AdjustDelay(struct structQDR2 *this, unsigned int delay) {

	unsigned int i=0;

	// set delay
	this->QDR2Regs->idelay = delay; //QDR2_GPAC2_IDELAY;

	// check if the idelay adjustment is done
	while ((this->QDR2Regs->idelay & QDR2_IDELAY_STABLE_MASK) == 0)
		if (++i>QDR2_IDELAY_TIMEOUT)
			return -1;

	return 0;
}


int structQDR2_new(struct structQDR2 *this, unsigned int base_addr) {

	this->QDR2Regs = (struct structQDR2Regs *)base_addr;
	this->qdr2AdjustDelay = qdr2AdjustDelay;

	return 0;
}
