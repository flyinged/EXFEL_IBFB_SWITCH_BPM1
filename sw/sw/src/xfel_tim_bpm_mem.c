/*
 * xfel_tim_bpm_mem.c
 *
 *  Created on: 10.11.2016
 *      Author: koprek_w
 */

#include "xfel_tim_bpm_mem.h"

/*
 * This driver extract information from the frames sent by XFEL timing receiver component in the SYS FPGA
 * The structure of the received data is as follows:
 *
 * |XXXXXXXX|XXXXXXXX|XXXXXXXT|DDDDDDDD|
 *
 * where
 *   X - not used
 *   T - when 0 means that DDDDDDDD is a data byte, otherwise it is a command byte
 *   D - data or command byte
 *
 * The command consists of CCCCIIII where
 *   CCCC - is a command code
 *   IIII - is a command identifier if exists
 */


int xfel_tim_bpm_mem_parse_extract_word(struct structXFELTIM *this, unsigned int ref, unsigned int *value) {

	int i;
	unsigned int reg, tmp=0 ;

	//xil_printf("\n\r");
	for (i=ref;i<ref+4;i++) {
		reg = *(this->mem+i);
		//xil_printf(" 0x%08X\n\r", reg);
		if (reg & 0x0000FF00) 	// this is command, data was expected
			return i-ref+1;		// returns number of bytes read so far
		tmp+=((reg & 0x000000FF)<<(8*(i-ref)));
	}
	//xil_printf("\n\r");

	*value = tmp;

	return 0;
}

int xfel_tim_bpm_mem_parse_train_params(struct structXFELTIM *this, unsigned int train, unsigned int ref) {

	int res;

	if ((res = xfel_tim_bpm_mem_parse_extract_word(this, ref, &this->timParams->trains[train].start)))
		return res;
	ref+=4;
	if ((res = xfel_tim_bpm_mem_parse_extract_word(this, ref, &this->timParams->trains[train].duration)))
		return res+4;
	ref+=4;
	if ((res = xfel_tim_bpm_mem_parse_extract_word(this, ref, &this->timParams->trains[train].increment)))
		return res+8;
	ref+=4;
	if ((res = xfel_tim_bpm_mem_parse_extract_word(this, ref, &this->timParams->trains[train].bunches)))
		return res+12;

	return 0;
}

int xfel_tim_bpm_mem_parse_frames(struct structXFELTIM *this) {
	int res;
	unsigned int i, fr;
	unsigned char cmd, ident, section;

	this->timParams->invalidCmd=0;
	this->timParams->invalidIdent=0;

	for (i=0;i<this->regs->rec_frames;){
		fr = *(this->mem+(i++));
		if (fr & 0x0000FF00) { 						// command frame
			cmd = fr & 0x000000FF;
			switch (cmd>>4) {
			case XFELTIM_CMD_TABLE:
				ident = cmd & 0x0F;					// identificator
				section = *(this->mem+(i++));		// skip section number
				switch (ident) {
				case XFELTIM_IDENT_TRAIN1:
				case XFELTIM_IDENT_TRAIN2:
				case XFELTIM_IDENT_TRAIN3:
					if ((res=xfel_tim_bpm_mem_parse_train_params(this, ident-XFELTIM_IDENT_TRAIN1, i))) {
						this->timParams->invalidData++;
						i+=res;
					}
					else {
						i+=16;
					}
					break;
				default:
					//xil_printf("Unknown table identifier 0x%02X\n\r", ident);
					this->timParams->invalidIdent++;
					break;
				}
				break;
			case XFELTIM_CMD_SHOT_ID:
				this->timParams->shotID = *(this->mem+(i++));
				break;
			default:
				//xil_printf("Unknown command 0x%02X\n\r", cmd);
				this->timParams->invalidCmd++;
				break;
			}
		}
		else {
			// skip invalid data
		}
	}

	return 0;
}

int structXFELTIM_new(struct structXFELTIM *this,	unsigned int xfeltim_reg_addr, unsigned int xfeltim_mem_addr) {

	this->regs = (struct structXFELTIMRegs *)xfeltim_reg_addr;
	this->mem = (unsigned int *)xfeltim_mem_addr;

	this->parse_frames = xfel_tim_bpm_mem_parse_frames;

	return 0;
}

