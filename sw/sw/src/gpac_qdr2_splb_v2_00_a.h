/*
 * gpac_qdr2_splb_v2_00_a.h
 *
 *  Created on: 10.07.2013
 *      Author: koprek_w
 */

#ifndef GPAC_QDR2_SPLB_V2_00_A_H_
#define GPAC_QDR2_SPLB_V2_00_A_H_

#define QDR2_REG_IDELAY_CTRL		0x00000008
#define QDR2_REG_IDELAY_STATUS		0x00000008

#define QDR2_GPAC2_IDELAY			30

#define QDR2_IDELAY_STABLE_MASK		0x00000040
#define QDR2_IDELAY_TIMEOUT			100000



struct structQDR2Regs {
	volatile unsigned int reset;
	volatile unsigned int pad1;
	volatile unsigned int idelay;
};

struct structQDR2 {
	struct structQDR2Regs *QDR2Regs;
	int (*qdr2AdjustDelay)(struct structQDR2 *this, unsigned int delay);
};

int structQDR2_new(struct structQDR2 *this, unsigned int base_addr);

#endif /* GPAC_QDR2_SPLB_V2_00_A_H_ */
