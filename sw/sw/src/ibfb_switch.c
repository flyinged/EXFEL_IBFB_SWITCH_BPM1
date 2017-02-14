/*
 * ibfb_switch.c
 *
 *  Created on: 08.01.2016
 *      Author: koprek_w
 */

#include <string.h>
#include "ibfb_switch.h"
#include "shell_utility.h"

/*
 * 0.3 : added "init" command
 * 0.4 : added "reset LOS counters" command, corrected packet display
 * 0.5 : added display of additional information to "print status" command
 * 0.6 : updated status display
 * 0.7 : added support for CRC error counter
 * 1.0 : First release
 * 1.1 : improvements ins data display.
 * 1.2 : show FW version reg
 * 1.3 : added error counter reset to init procedure
 * 1.4 : removed debug FIFO, updated init procedures (routing tables), added "read stats", added ping functions
 * 1.5 : added support for QDR2 and statistics
 */
#define VMAJ 1
#define VMIN 5

//const char * const cname[] = { "SFP0", "SFP1", "SFP2", "SFP3", "P0.0", "P0.1", "BPM0", "BPM1", "BPM2", "BPM3"};
const char * const losname[] = { "        SYNC", "      RESYNC", "   SYNC_LOST", "    BAD_CODE"};
const char * const fifo_st[] = { "DATA AVAILABLE", "EMPTY", "FULL", "ERROR"};
const unsigned char CH[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int ibfb_switch_init(struct structIBFBSwitch *this);


/*
 * Display status of switch
 * 1. display GTX status
 */
int ibfb_switch_print_status(struct structIBFBSwitch *this) {

	unsigned int  loscnt0, loscnt1;

	//Serial
	xil_printf("\n\r*** FW SERIAL = 0x%08X ***\n\r", this->regs->fw_serial);
	//xil_printf("\n\r*** FW SERIAL = %d ***\n\r", this->reg[31]);

	/****************************GTX STATUS********************************/
//	status_qb = this->reg[REG_MGT_QB];
//	status_p0 = this->reg[REG_MGT_P0];
//	lb_qb     = this->reg[REG_LB_QB];
//	lb_p0     = this->reg[REG_LB_P0];
//	bpmid13   = this->reg[REG_FILT13_BPM_ID];
//	bpmid02   = this->reg[REG_FILT02_BPM_ID];
	//status_f  = this->reg[REG_DFIFO];

	//tile lock
	print("\n\r");
	print("LOCK : QSFP13 | QSFP02 | BPM01 | BPM23 | P0\n\r");
	xil_printf("            %d |      %d |     %d |     %d |  %d\n\r", \
			(this->regs->mgt_q13_status &1)?1:0, \
					(this->regs->mgt_q02_status &1)?1:0, \
							(this->regs->mgt_b01_status &1)?1:0, \
									(this->regs->mgt_b23_status &1)?1:0,  \
											(this->regs->mgt_p0_status &1)?1:0  \
	);
	/*
		(status_qb&REG_MGT_Q13_LOCK)?1:0, \
		(status_qb&REG_MGT_Q02_LOCK)?1:0, \
		(status_qb&REG_MGT_B01_LOCK)?1:0, \
		(status_qb&REG_MGT_B23_LOCK)?1:0,  \
		(status_p0&REG_MGT_P0_LOCK)?1:0  \
		);
	 */
	xil_printf("MGT RX SYNC (BPM,P0,QSFP) = 0x%03X\n\r", ((this->regs->rxsync_MSB<<8) | this->regs->rxsync_LSB ) );
	//Per channel
	print("\n\r");
	print("CHAN  : RST_DONE | LOSS OF SYNC | LOOPBACK\n\r");
	xil_printf("QSFP0 :        %d | %s |        %d%s\n\r", \
			(this->regs->mgt_q02_status &4)?1:0, //rst done
					losname[(this->regs->mgt_q02_status & 0xC0)>>6], //LOS
					(this->regs->loopback_qsfp01 & 0xF),
					(this->regs->loopback_qsfp01 & 0xF)?"*":""
	);
	/*
		(status_qb&REG_Q0_RSTD)?1:0,
		losname[(status_qb&REG_Q0_LOS)>>14],
		(lb_qb&REG_LB_Q0),
		(lb_qb&REG_LB_Q0)?"*":""
		);*/
	xil_printf("QSFP1 :        %d | %s |        %d%s\n\r", \
			(this->regs->mgt_q13_status &4)?1:0, //rst done
					losname[(this->regs->mgt_q13_status & 0xC0)>>6], //LOS
					(this->regs->loopback_qsfp01 & 0xF0)>>4,
					(this->regs->loopback_qsfp01 & 0xF0)?"*":""
	);
	xil_printf("QSFP2 :        %d | %s |        %d%s\n\r", \
			(this->regs->mgt_q02_status &2)?1:0, //rst done
					losname[(this->regs->mgt_q02_status & 0x30)>>4], //LOS
					(this->regs->loopback_qsfp23 & 0xF),
					(this->regs->loopback_qsfp23 & 0xF)?"*":""
	);
	xil_printf("QSFP3 :        %d | %s |        %d%s\n\r", \
			(this->regs->mgt_q13_status &2)?1:0, //rst done
					losname[(this->regs->mgt_q13_status & 0x30)>>4], //LOS
					(this->regs->loopback_qsfp23 & 0xF0)>>4,
					(this->regs->loopback_qsfp23 & 0xF0)?"*":""
	);
	xil_printf("P0.0  :        %d | %s |        %d%s\n\r", \
			(this->regs->mgt_p0_status &2)?1:0, //rst done
					losname[(this->regs->mgt_p0_status & 0x30)>>4], //LOS
					(this->regs->loopback_p0 & 0xF),
					(this->regs->loopback_p0 & 0xF)?"*":""
	);
	xil_printf("P0.1  :        %d | %s |        %d%s\n\r", \
			(this->regs->mgt_p0_status &4)?1:0, //rst done
					losname[(this->regs->mgt_p0_status & 0xC0)>>6], //LOS
					(this->regs->loopback_p0 & 0xF0)>>4,
					(this->regs->loopback_p0 & 0xF0)?"*":""
	);
	xil_printf("BPM0  :        %d | %s |        %d%s\n\r", \
			(this->regs->mgt_b01_status &2)?1:0, //rst done
					losname[(this->regs->mgt_b01_status & 0x30)>>4], //LOS
					(this->regs->loopback_bpm01 & 0xF),
					(this->regs->loopback_bpm01 & 0xF)?"*":""
	);
	xil_printf("BPM1  :        %d | %s |        %d%s\n\r", \
			(this->regs->mgt_b01_status &4)?1:0, //rst done
					losname[(this->regs->mgt_b01_status & 0xC0)>>6], //LOS
					(this->regs->loopback_bpm01 & 0xF0)>>4,
					(this->regs->loopback_bpm01 & 0xF0)?"*":""
	);
	xil_printf("BPM2  :        %d | %s |        %d%s\n\r", \
			(this->regs->mgt_b23_status &2)?1:0, //rst done
					losname[(this->regs->mgt_b23_status & 0x30)>>4], //LOS
					(this->regs->loopback_bpm23 & 0xF),
					(this->regs->loopback_bpm23 & 0xF)?"*":""
	);
	xil_printf("BPM3  :        %d | %s |        %d%s\n\r", \
			(this->regs->mgt_b23_status &4)?1:0, //rst done
					losname[(this->regs->mgt_b23_status & 0xC0)>>6], //LOS
					(this->regs->loopback_bpm23 & 0xF0)>>4,
					(this->regs->loopback_bpm23 & 0xF0)?"*":""
	);

	print("\n\rLOSS OS SYNC COUNTERS:\n\r");
	loscnt0  = this->regs->los_cnt_qsfp0; //this->reg[REG_LCNT_Q10];
	loscnt1  = this->regs->los_cnt_qsfp1; //(loscnt0>>16) & 0xFFFF;
	xil_printf("    SFP0: 0x%04X %s\n\r", loscnt0, loscnt0?"*":"");
	xil_printf("    SFP1: 0x%04X %s\n\r", loscnt1, loscnt1?"*":"");
	loscnt0  = this->regs->los_cnt_qsfp2;
	loscnt1  = this->regs->los_cnt_qsfp3;
	xil_printf("    SFP2: 0x%04X %s\n\r", loscnt0, loscnt0?"*":"");
	xil_printf("    SFP3: 0x%04X %s\n\r", loscnt1, loscnt1?"*":"");
	loscnt0  = this->regs->los_cnt_p00;
	loscnt1  = this->regs->los_cnt_p01;
	xil_printf("    P0_0: 0x%04X %s\n\r", loscnt0, loscnt0?"*":"");
	xil_printf("    P0_1: 0x%04X %s\n\r", loscnt1, loscnt1?"*":"");
	loscnt0  = this->regs->los_cnt_bpm0;
	loscnt1  = this->regs->los_cnt_bpm1;
	xil_printf("    BPM0: 0x%04X %s\n\r", loscnt0, loscnt0?"*":"");
	xil_printf("    BPM1: 0x%04X %s\n\r", loscnt1, loscnt1?"*":"");
	loscnt0  = this->regs->los_cnt_bpm2;
	loscnt1  = this->regs->los_cnt_bpm3;
	xil_printf("    BPM2: 0x%04X %s\n\r", loscnt0, loscnt0?"*":"");
	xil_printf("    BPM3: 0x%04X %s\n\r", loscnt1, loscnt1?"*":"");

	/**************************** Switch specific info *******************************/
	//K SOP/EOP
	print("\n\r");
	xil_printf("K_SOP = 0x%02X\n\r", this->regs->k_sop);
	xil_printf("K_EOP = 0x%02X\n\r", this->regs->k_eop);

	//BPM IDs
	print("\n\r");
	xil_printf("Filter 02 BPM IDs (X,X,Y,Y): 0x%02X, 0x%02X, 0x%02X, 0x%02X\n\r", \
			this->regs->filt02_bpm_x[0], this->regs->filt02_bpm_x[1], this->regs->filt02_bpm_y[0], this->regs->filt02_bpm_y[1]);
	xil_printf("Filter 13 BPM IDs (X,X,Y,Y): 0x%02X, 0x%02X, 0x%02X, 0x%02X\n\r", \
			this->regs->filt13_bpm_x[0], this->regs->filt13_bpm_x[1], this->regs->filt13_bpm_y[0], this->regs->filt13_bpm_y[1]);

	//Bucket range filters
	print("\n\r");
	xil_printf("Filter 02 bucket range (min,max): (%d, %d)\n\r", this->regs->filt02_bucket_start, this->regs->filt02_bucket_stop);
	xil_printf("Filter 13 bucket range (min,max): (%d, %d)\n\r", this->regs->filt13_bucket_start, this->regs->filt13_bucket_stop);

	print("\n\r");
	xil_printf("Ping Packets Enable (SFP 0,1,2,3): %d, %d, %d, %d\n\r", \
			this->regs->ping_en_sfp0, this->regs->ping_en_sfp1, this->regs->ping_en_sfp2, this->regs->ping_en_sfp3);


	print("\n\r");

	return 0;
}

/*
 * Print IBFB Switch's statistics
 */
int ibfb_switch_print_stats(struct structIBFBSwitch *this) {
	int i, first_bin;

	this->ddr_mem->stats_ena = 0; //disable interrupt (avoid reading DDR while it's being changed)

	/* Packet counters */
	print("\n\rIBFB Switch packet statistics:\n\r");
	xil_printf("    Filt02 Received Packets (0,2) : %05d, %05d\n\r", this->regs->sfp_in_packets[0], this->regs->sfp_in_packets[1]);
	xil_printf("    Filt13 Received Packets (1,3) : %05d, %05d\n\r", this->regs->sfp_in_packets[2], this->regs->sfp_in_packets[3]);
	print("\n\r");
	xil_printf("    Filt02 Discarded Packets (X,Y): %05d, %05d\n\r", this->regs->filt02_discard_x, this->regs->filt02_discard_y);
	xil_printf("    Filt13 Discarded Packets (X,Y): %05d, %05d\n\r", this->regs->filt13_discard_x, this->regs->filt13_discard_y);
	print("\n\r");
	xil_printf("    Filt02 Passed Packets (X,Y)   : %05d, %05d\n\r", this->regs->filt02_passed_x, this->regs->filt02_passed_y);
	xil_printf("    Filt13 Passed Packets (X,Y)   : %05d, %05d\n\r", this->regs->filt13_passed_x, this->regs->filt13_passed_y);
	print("\n\r");
	xil_printf("    First Bad BPM ID (Filt 02,13) :  0x%02X,  0x%02X\n\r", this->regs->filt02_bad_bpm_id, this->regs->filt13_bad_bpm_id);
	print("\n\r");

	/* PING statistics */
	print("\n\rIBFB Switch PING statistics:\n\r");
	xil_printf("    Ping Enable (SFP 0:3)  :  %d, %d, %d, %d\n\r", \
			this->regs->ping_en_sfp0, this->regs->ping_en_sfp1, this->regs->ping_en_sfp2, this->regs->ping_en_sfp3);
	xil_printf("    Ping Received (SFP 0:3):  %d, %d, %d, %d\n\r", \
			this->regs->ping_rx_sfp0, this->regs->ping_rx_sfp1, this->regs->ping_rx_sfp2, this->regs->ping_rx_sfp3);
	xil_printf("    Ping Latency 0         :  %d ckc, %d ns\n\r", this->regs->ping_latency_sfp0, (4615*this->regs->ping_latency_sfp0)/1000);
	xil_printf("    Ping Latency 1         :  %d ckc, %d ns\n\r", this->regs->ping_latency_sfp1, (4615*this->regs->ping_latency_sfp1)/1000);
	xil_printf("    Ping Latency 2         :  %d ckc, %d ns\n\r", this->regs->ping_latency_sfp2, (4615*this->regs->ping_latency_sfp2)/1000);
	xil_printf("    Ping Latency 3         :  %d ckc, %d ns\n\r", this->regs->ping_latency_sfp3, (4615*this->regs->ping_latency_sfp3)/1000);

	/* Interrupt statistics */
	xil_printf("\n\rInterrupt counter = 0x%08X\n\r", this->ddr_mem->interrupt_counter);
	xil_printf("INT execution time (last, [min,max]) = %d [%d,%d] ns\n\r", 8*this->ddr_mem->last_execution_time, \
			8*this->ddr_mem->min_execution_time,
			8*this->ddr_mem->max_execution_time);

	/* SW computed packet statistics */
	if (this->qdr_status) {
		print("\n\r*** WARNING: QDR memory not synchronized. Cannot compute packet statistics ***\n\r");
	} else {
		/* Packets received per BPM_ID */
		print("\n\rNumber of Packets per BPM ID\n\r");
		//          00     | 00000 | 00000 | 00000 | 00000 | 00000
		print(     "     SFP | IDX0  | IDX1  | IDY0  | IDY1  | BAD_ID\n\r");
		print(     "-------------------------------------------------\n\r");
		xil_printf("         | 0x%02X  | 0x%02X  | 0x%02X  | 0x%02X  |\n\r", \
				this->regs->filt02_bpm_x[0], \
				this->regs->filt02_bpm_x[1], \
				this->regs->filt02_bpm_y[0], \
				this->regs->filt02_bpm_y[1]  \
		);
		print(     "-------------------------------------------------\n\r");
		xil_printf("      00 | %05d | %05d | %05d | %05d | %05d\n\r", \
				this->ddr_mem->sfp_bpm_cnt[0][0], \
				this->ddr_mem->sfp_bpm_cnt[0][1], \
				this->ddr_mem->sfp_bpm_cnt[0][2], \
				this->ddr_mem->sfp_bpm_cnt[0][3], \
				this->ddr_mem->sfp_bpm_cnt[0][4]
		);
		xil_printf("      02 | %05d | %05d | %05d | %05d | %05d\n\r", \
				this->ddr_mem->sfp_bpm_cnt[2][0], \
				this->ddr_mem->sfp_bpm_cnt[2][1], \
				this->ddr_mem->sfp_bpm_cnt[2][2], \
				this->ddr_mem->sfp_bpm_cnt[2][3], \
				this->ddr_mem->sfp_bpm_cnt[2][4]
		);
		print(     "-------------------------------------------------\n\r");
		xil_printf("         | 0x%02X  | 0x%02X  | 0x%02X  | 0x%02X  |\n\r", \
				this->regs->filt13_bpm_x[0], \
				this->regs->filt13_bpm_x[1], \
				this->regs->filt13_bpm_y[0], \
				this->regs->filt13_bpm_y[1]  \
		);
		print(     "-------------------------------------------------\n\r");
		xil_printf("      01 | %05d | %05d | %05d | %05d | %05d\n\r", \
				this->ddr_mem->sfp_bpm_cnt[1][0], \
				this->ddr_mem->sfp_bpm_cnt[1][1], \
				this->ddr_mem->sfp_bpm_cnt[1][2], \
				this->ddr_mem->sfp_bpm_cnt[1][3], \
				this->ddr_mem->sfp_bpm_cnt[1][4]
		);
		xil_printf("      03 | %05d | %05d | %05d | %05d | %05d\n\r", \
				this->ddr_mem->sfp_bpm_cnt[3][0], \
				this->ddr_mem->sfp_bpm_cnt[3][1], \
				this->ddr_mem->sfp_bpm_cnt[3][2], \
				this->ddr_mem->sfp_bpm_cnt[3][3], \
				this->ddr_mem->sfp_bpm_cnt[3][4]
		);

		/* Bad BPM ID counters */
		xil_printf("\n\rTotal number of bunches with bad BPM IDs (filt02, filt13): %d, %d\n\r", \
				this->ddr_mem->filt02_bad_bpm_cnt, \
				this->ddr_mem->filt13_bad_bpm_cnt);

		/* Packet Delay Histograms */
		first_bin = this->ddr_mem->ipt_histo_center_bin - this->ddr_mem->ipt_histo_hwidth;
		xil_printf("\n\rIntra-packet delay (IPD) - Histogram (C=%d, HW=%d)\n\r", \
				this->ddr_mem->ipt_histo_center_bin, \
				this->ddr_mem->ipt_histo_hwidth
				);
		print("    IPD ||             SFP0            ||            SFP1             ||            SFP2             ||            SFP3\n\r");
		print("        || X0  | X1  | Y0  | Y1  | BAD || X0  | X1  | Y0  | Y1  | BAD || X0  | X1  | Y0  | Y1  | BAD || X0  | X1  | Y0  | Y1  | BAD\n\r");
		//         000 || 000 | 000 | 000 | 000 | 000 || 000 | 000 | 000 | 000 | 000 || 000 | 000 | 000 | 000 | 000 || 000 | 000 | 000 | 000 | 000
		xil_printf("  <=%03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d\n\r", \
				first_bin, \
				this->ddr_mem->sfp_ipt_histo[0][0][0], \
				this->ddr_mem->sfp_ipt_histo[0][1][0], \
				this->ddr_mem->sfp_ipt_histo[0][2][0], \
				this->ddr_mem->sfp_ipt_histo[0][3][0], \
				this->ddr_mem->sfp_ipt_histo[0][4][0], \
				this->ddr_mem->sfp_ipt_histo[1][0][0], \
				this->ddr_mem->sfp_ipt_histo[1][1][0], \
				this->ddr_mem->sfp_ipt_histo[1][2][0], \
				this->ddr_mem->sfp_ipt_histo[1][3][0], \
				this->ddr_mem->sfp_ipt_histo[1][4][0], \
				this->ddr_mem->sfp_ipt_histo[2][0][0], \
				this->ddr_mem->sfp_ipt_histo[2][1][0], \
				this->ddr_mem->sfp_ipt_histo[2][2][0], \
				this->ddr_mem->sfp_ipt_histo[2][3][0], \
				this->ddr_mem->sfp_ipt_histo[2][4][0], \
				this->ddr_mem->sfp_ipt_histo[3][0][0], \
				this->ddr_mem->sfp_ipt_histo[3][1][0], \
				this->ddr_mem->sfp_ipt_histo[3][2][0], \
				this->ddr_mem->sfp_ipt_histo[3][3][0], \
				this->ddr_mem->sfp_ipt_histo[3][4][0]  \
				);
		for(i=1; i<(2*this->ddr_mem->ipt_histo_hwidth); i++) {
			xil_printf("    %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d\n\r", \
							first_bin+i, \
							this->ddr_mem->sfp_ipt_histo[0][0][i], \
							this->ddr_mem->sfp_ipt_histo[0][1][i], \
							this->ddr_mem->sfp_ipt_histo[0][2][i], \
							this->ddr_mem->sfp_ipt_histo[0][3][i], \
							this->ddr_mem->sfp_ipt_histo[0][4][i], \
							this->ddr_mem->sfp_ipt_histo[1][0][i], \
							this->ddr_mem->sfp_ipt_histo[1][1][i], \
							this->ddr_mem->sfp_ipt_histo[1][2][i], \
							this->ddr_mem->sfp_ipt_histo[1][3][i], \
							this->ddr_mem->sfp_ipt_histo[1][4][i], \
							this->ddr_mem->sfp_ipt_histo[2][0][i], \
							this->ddr_mem->sfp_ipt_histo[2][1][i], \
							this->ddr_mem->sfp_ipt_histo[2][2][i], \
							this->ddr_mem->sfp_ipt_histo[2][3][i], \
							this->ddr_mem->sfp_ipt_histo[2][4][i], \
							this->ddr_mem->sfp_ipt_histo[3][0][i], \
							this->ddr_mem->sfp_ipt_histo[3][1][i], \
							this->ddr_mem->sfp_ipt_histo[3][2][i], \
							this->ddr_mem->sfp_ipt_histo[3][3][i], \
							this->ddr_mem->sfp_ipt_histo[3][4][i]  \
					);
		}
		xil_printf("  >=%03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d\n\r", \
				first_bin+i, \
				this->ddr_mem->sfp_ipt_histo[0][0][i], \
				this->ddr_mem->sfp_ipt_histo[0][1][i], \
				this->ddr_mem->sfp_ipt_histo[0][2][i], \
				this->ddr_mem->sfp_ipt_histo[0][3][i], \
				this->ddr_mem->sfp_ipt_histo[0][4][i], \
				this->ddr_mem->sfp_ipt_histo[1][0][i], \
				this->ddr_mem->sfp_ipt_histo[1][1][i], \
				this->ddr_mem->sfp_ipt_histo[1][2][i], \
				this->ddr_mem->sfp_ipt_histo[1][3][i], \
				this->ddr_mem->sfp_ipt_histo[1][4][i], \
				this->ddr_mem->sfp_ipt_histo[2][0][i], \
				this->ddr_mem->sfp_ipt_histo[2][1][i], \
				this->ddr_mem->sfp_ipt_histo[2][2][i], \
				this->ddr_mem->sfp_ipt_histo[2][3][i], \
				this->ddr_mem->sfp_ipt_histo[2][4][i], \
				this->ddr_mem->sfp_ipt_histo[3][0][i], \
				this->ddr_mem->sfp_ipt_histo[3][1][i], \
				this->ddr_mem->sfp_ipt_histo[3][2][i], \
				this->ddr_mem->sfp_ipt_histo[3][3][i], \
				this->ddr_mem->sfp_ipt_histo[3][4][i]  \
				);


		print("\n\rDelay limits\n\r");
		print(     " LIMITS ||             SFP0            ||            SFP1             ||            SFP2             ||            SFP3\n\r");
		print(     "        || X0  | X1  | Y0  | Y1  | BAD || X0  | X1  | Y0  | Y1  | BAD || X0  | X1  | Y0  | Y1  | BAD || X0  | X1  | Y0  | Y1  | BAD\n\r");
		xil_printf(" IPTMIN || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d\n\r", \
				IPT_MIN(this->ddr_mem->ipt_min[0][0]), \
				IPT_MIN(this->ddr_mem->ipt_min[0][1]), \
				IPT_MIN(this->ddr_mem->ipt_min[0][2]), \
				IPT_MIN(this->ddr_mem->ipt_min[0][3]), \
				IPT_MIN(this->ddr_mem->ipt_min[0][4]), \
				IPT_MIN(this->ddr_mem->ipt_min[1][0]), \
				IPT_MIN(this->ddr_mem->ipt_min[1][1]), \
				IPT_MIN(this->ddr_mem->ipt_min[1][2]), \
				IPT_MIN(this->ddr_mem->ipt_min[1][3]), \
				IPT_MIN(this->ddr_mem->ipt_min[1][4]), \
				IPT_MIN(this->ddr_mem->ipt_min[2][0]), \
				IPT_MIN(this->ddr_mem->ipt_min[2][1]), \
				IPT_MIN(this->ddr_mem->ipt_min[2][2]), \
				IPT_MIN(this->ddr_mem->ipt_min[2][3]), \
				IPT_MIN(this->ddr_mem->ipt_min[2][4]), \
				IPT_MIN(this->ddr_mem->ipt_min[3][0]), \
				IPT_MIN(this->ddr_mem->ipt_min[3][1]), \
				IPT_MIN(this->ddr_mem->ipt_min[3][2]), \
				IPT_MIN(this->ddr_mem->ipt_min[3][3]), \
				IPT_MIN(this->ddr_mem->ipt_min[3][4])  \
				);
		xil_printf(" IPTMAX || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d || %03d | %03d | %03d | %03d | %03d\n\r", \
						IPT_MAX(this->ddr_mem->ipt_max[0][0]), \
						IPT_MAX(this->ddr_mem->ipt_max[0][1]), \
						IPT_MAX(this->ddr_mem->ipt_max[0][2]), \
						IPT_MAX(this->ddr_mem->ipt_max[0][3]), \
						IPT_MAX(this->ddr_mem->ipt_max[0][4]), \
						IPT_MAX(this->ddr_mem->ipt_max[1][0]), \
						IPT_MAX(this->ddr_mem->ipt_max[1][1]), \
						IPT_MAX(this->ddr_mem->ipt_max[1][2]), \
						IPT_MAX(this->ddr_mem->ipt_max[1][3]), \
						IPT_MAX(this->ddr_mem->ipt_max[1][4]), \
						IPT_MAX(this->ddr_mem->ipt_max[2][0]), \
						IPT_MAX(this->ddr_mem->ipt_max[2][1]), \
						IPT_MAX(this->ddr_mem->ipt_max[2][2]), \
						IPT_MAX(this->ddr_mem->ipt_max[2][3]), \
						IPT_MAX(this->ddr_mem->ipt_max[2][4]), \
						IPT_MAX(this->ddr_mem->ipt_max[3][0]), \
						IPT_MAX(this->ddr_mem->ipt_max[3][1]), \
						IPT_MAX(this->ddr_mem->ipt_max[3][2]), \
						IPT_MAX(this->ddr_mem->ipt_max[3][3]), \
						IPT_MAX(this->ddr_mem->ipt_max[3][4])  \
						);
	}

	this->ddr_mem->stats_ena = 1; //re-enable interrupt

	return 0;
}

/*
 * Resets all GTX tiles, filter, router, debug FIFO, enable debug FIFO
 */
int ibfb_switch_gtx_init(struct structIBFBSwitch *this) {

	// reset all GTX
	this->regs->reset = 0; //this->reg[REG_RST] = 0;
	this->regs->reset = REG_RST_ALL; //this->reg[REG_RST] = REG_RST_ALL;  //reset all
	this->regs->reset = 0; //this->reg[REG_RST] = 0; //release resets and enable debug FIFO
	print("\n\rReset all GTX\n\r");

	return 0;
}

int ibfb_switch_rst_lcnt(struct structIBFBSwitch *this) {

	unsigned int reg;

	reg = this->regs->reset;
	this->regs->reset = reg | REG_RST_LCNT_ALL;  //reset LOS counters
	this->regs->reset = reg & (~REG_RST_LCNT_ALL);  //release resets
	//reg = this->reg[REG_RST];
	//this->reg[REG_RST] = reg | REG_RST_LCNT_ALL;  //reset LOS counters
	//this->reg[REG_RST] = reg & (~REG_RST_LCNT_ALL);  //release resets
	print("\n\rReset all LOS counters\n\r");

	return 0;
}

/*
 * Set loopback value for selected GTX channel
 */
int ibfb_switch_set_loopback(struct structIBFBSwitch *this, char chan, unsigned long data) {
	unsigned long reg;

		if (chan > 9) {
			return 1;
		}

//		if (data == 3 || data == 5 || data > 6) {
//			return 2;
//		}

		//get current loopback
		switch (chan) {
		case 0:
		case 1:
			reg = this->regs->loopback_qsfp01;
			xil_printf("Current loopback register (QSFP01) = 0x%02X\n\r", reg);
			break;
		case 2:
		case 3:
			reg = this->regs->loopback_qsfp23;
			xil_printf("Current loopback register (QSFP23) = 0x%02X\n\r", reg);
			break;
		case 4:
		case 5:
			reg = this->regs->loopback_p0;
			xil_printf("Current loopback register (P0) = 0x%02X\n\r", reg);
			break;
		case 6:
		case 7:
			reg = this->regs->loopback_bpm01;
			xil_printf("Current loopback register (BPM01) = 0x%02X\n\r", reg);
			break;
		case 8:
		case 9:
			reg = this->regs->loopback_bpm23;
			xil_printf("Current loopback register (BPM23) = 0x%02X\n\r", reg);
			break;
		}


		switch (chan) {
		case 0:
			//reset current value
			reg &= ~0xF;
			//set new value
			reg |= data;
			this->regs->loopback_qsfp01 = reg;
			xil_printf("%d: New loopback register (QSFP01) = 0x%08X\n\r", chan, this->regs->loopback_qsfp01);
			break;
		case 1:
			//reset current value
			reg &= ~0xF0;
			//set new value
			reg |= data<<4;
			this->regs->loopback_qsfp01 = reg;
			xil_printf("%d: New loopback register (QSFP01) = 0x%08X\n\r", chan, this->regs->loopback_qsfp01);
			break;
		case 2:
			//reset current value
			reg &= ~0xF;
			//set new value
			reg |= data;
			this->regs->loopback_qsfp23 = reg;
			xil_printf("%d: New loopback register (QSFP23) = 0x%08X\n\r", chan, this->regs->loopback_qsfp23);
			break;
		case 3:
			//reset current value
			reg &= ~0xF0;
			//set new value
			reg |= data<<4;
			this->regs->loopback_qsfp23 = reg;
			xil_printf("%d: New loopback register (QSFP23) = 0x%08X\n\r", chan, this->regs->loopback_qsfp23);
			break;
		case 4:
			//reset current value
			reg &= ~0xF;
			//set new value
			reg |= data;
			this->regs->loopback_p0 = reg;
			xil_printf("%d: New loopback register (P0) = 0x%08X\n\r", chan, this->regs->loopback_p0);
			break;
		case 5:
			//reset current value
			reg &= ~0xF0;
			//set new value
			reg |= data<<4;
			this->regs->loopback_p0 = reg;
			xil_printf("%d: New loopback register (P0) = 0x%08X\n\r", chan, this->regs->loopback_p0);
			break;
		case 6:
			//reset current value
			reg &= ~0xF;
			//set new value
			reg |= data;
			this->regs->loopback_qsfp01 = reg;
			xil_printf("%d: New loopback register (QSFP01) = 0x%08X\n\r", chan, this->regs->loopback_qsfp01);
			break;
		case 7:
			//reset current value
			reg &= ~0xF0;
			//set new value
			reg |= data<<4;
			this->regs->loopback_qsfp01 = reg;
			xil_printf("%d: New loopback register (QSFP01) = 0x%08X\n\r", chan, this->regs->loopback_qsfp01);
			break;
		case 8:
			//reset current value
			reg &= ~0xF;
			//set new value
			reg |= data;
			this->regs->loopback_qsfp23 = reg;
			xil_printf("%d: New loopback register (QSFP23) = 0x%08X\n\r", chan, this->regs->loopback_qsfp23);
			break;
		case 9:
			//reset current value
			reg &= ~0xF0;
			//set new value
			reg |= data<<4;
			this->regs->loopback_qsfp23 = reg;
			xil_printf("%d: New loopback register (QSFP23) = 0x%08X\n\r", chan, this->regs->loopback_qsfp23);
			break;
		default:
			return 1;
		}

		return 0;
}

/*
 * Set ping-transmission enable
 */
int ibfb_switch_set_ping_en(struct structIBFBSwitch *this, char chan) {
	if (chan > 0xF) {
		return 1;
			} else {
		if (chan & 1) {
			this->regs->ping_en_sfp3 = 1;
			} else {
			this->regs->ping_en_sfp3 = 0;
			}
		if (chan & 2) {
			this->regs->ping_en_sfp2 = 1;
			} else {
			this->regs->ping_en_sfp2 = 0;
			}
		if (chan & 4) {
			this->regs->ping_en_sfp1 = 1;
				} else {
			this->regs->ping_en_sfp1 = 0;
				}
		if (chan & 8) {
			this->regs->ping_en_sfp0 = 1;
			} else {
			this->regs->ping_en_sfp0 = 0;
		}
	}
		return 0;
}


int ibfb_switch_print_qdr_packets(struct structIBFBSwitch *this, unsigned int sfp, unsigned int first, unsigned int amount) {

	unsigned int i, qid;

	xil_printf("\n\r*** SFP %d ***\n\r", sfp);

	if (sfp > 3) {
		print("Bad SFP is\n\r");
		return -1;
	} else if (sfp == 1) qid = 2;
	  else if (sfp == 2) qid = 1;
	  else              qid = sfp;

//	xil_printf(" TIMESTAMP BASE ADDRESS = 0x%08X\n\r",   this->qdr_mem->sfp_rx[qid].timestamp);
//	xil_printf(" CONTROL   BASE ADDRESS = 0x%08X\n\r",   this->qdr_mem->sfp_rx[qid].control);
//	xil_printf(" XPOS      BASE ADDRESS = 0x%08X\n\r",   this->qdr_mem->sfp_rx[qid].xpos);
//	xil_printf(" YPOS      BASE ADDRESS = 0x%08X\n\n\r", this->qdr_mem->sfp_rx[qid].ypos);


	//print("  00000: 0x00000000 | 0x00, 0x00, 0x0000 | 0x00000000, 0x00000000");
	  print("    PKT: TIMESTAMP  | CTRL,  BPM, BUCKET | X-POSITION, Y-POSITION\n\r");
	for (i=first; i < first+amount; i++) {
		xil_printf("  %05d: 0x%08X | 0x%02X, 0x%02X, 0x%04X | 0x%08X, 0x%08X\n\r", \
				     i, \
					 this->qdr_mem->sfp_rx[qid].timestamp[i], \
					(this->qdr_mem->sfp_rx[qid].control[i]>>24) & 0xFF, \
					(this->qdr_mem->sfp_rx[qid].control[i]>>16) & 0xFF, \
					(this->qdr_mem->sfp_rx[qid].control[i]    ) & 0xFFFF, \
					(this->qdr_mem->sfp_rx[qid].xpos[i]    ), \
					(this->qdr_mem->sfp_rx[qid].ypos[i]    ) \
					);
	}

	return 0;
}


int ibfb_ctrl_update_timing(struct structIBFBSwitch *this) {

	this->regs->bunch_delay = this->functions->bunch_delay;
	this->regs->bucket_number = IBFB_CTRL_XFEL_BUCKET_NUMBER;
	this->regs->bucket_space = IBFB_CTRL_XFEL_BUCKET_SPACE;
	this->regs->trg_enabled = 1;
	this->regs->trg_mode = this->functions->trg_mode;
	if (this->functions->trg_source)
		this->regs->trg_source = 1;		// 1 - auto
	else
		this->regs->trg_source = 0;		// 0 - external
	this->regs->trg_rate = this->functions->trg_source;

	return 0;
}

void ibfb_ctrl_function_process(void *funcUserObject, unsigned int func) {

	struct structIBFBSwitch *this = (struct structIBFBSwitch *)funcUserObject;
	//unsigned char idx;

	switch (func*4) {
	case 0x000 :
		break;
	case 0x004 :
	case 0x008 :
	case 0x00C :
		ibfb_ctrl_update_timing(this);
		break;
	}

	return;
}


/****************************************************************************
 * Execute shell commands
 ****************************************************************************/
int ibfb_switch_ibfb_cmd(void *object, int argc, char *argv[]){

	unsigned char cmd, *cptr;
	unsigned char chan;
	unsigned long data, i; //, start, n, i, bid02, bid13;
	//int i;
	struct structIBFBSwitch *this = (struct structIBFBSwitch*)(object);

	if (argc>1)
		cmd = argv[1][0];
	else //ibfb == 1
		cmd = 0xFF;
		//return -1;

	switch (cmd) {
	case '0': /* RESET */
		ibfb_switch_init(this);
		break;
	case '1': //print all status data
		print("RAW REGISTER MAP\n\r");
		//     N   : 0x 00.00.00.00 (0x00000000 0x00000000)
		for (data = 0; data < NREGS; data++) {
			xil_printf("  0x%02X (%02d): 0x%08X\n\r", 4*data, data, this->reg[data]);
		}
		break;
	case '2':
		ibfb_switch_print_qdr_packets(this, 0, 0, 10);
		ibfb_switch_print_qdr_packets(this, 0, 2600, 10);

		ibfb_switch_print_qdr_packets(this, 1, 0, 10);
		ibfb_switch_print_qdr_packets(this, 1, 2600, 10);

		ibfb_switch_print_qdr_packets(this, 2, 0, 10);
		ibfb_switch_print_qdr_packets(this, 2, 2600, 10);

		ibfb_switch_print_qdr_packets(this, 3, 0, 10);
		ibfb_switch_print_qdr_packets(this, 3, 2600, 10);
		break;
	case 'a': /* DISPLAY STATUS */
		ibfb_switch_print_status(this);
		break;
	case 'b': /* SET FILTERS */
		if (argc != 7) {
			print("\n\rUSAGE:\n\r");
			print("    switch b FILTER IDX0 IDX1 IDY0 IDY1\n\r");
			print("    FILTER: 0=>FILT02, 1=>FILT13\n\r");
			print("    ID_VEC: IDX0 & IDX1 & IDY0 & IDY1 (hex32)\n\r");
			print("\n\r");
		} else {
			chan = atoi(argv[2]);
			cptr = (unsigned char*) &data;
			cptr[0] = strtol(argv[3], NULL, 0);
			cptr[1] = strtol(argv[4], NULL, 0);
			cptr[2] = strtol(argv[5], NULL, 0);
			cptr[3] = strtol(argv[6], NULL, 0);
			xil_printf("\n\rSetting BPM IDs for channel %d to (X,X,Y,Y):\n\r", chan);
			xil_printf("    0x%02X, 0x%02X, 0x%02X, 0x%02X\n\r", \
					cptr[0], cptr[1], cptr[2], cptr[3]);
			if (chan == 0) {
				this->regs->filt02_bpm_x[0] = cptr[0];
				this->regs->filt02_bpm_x[1] = cptr[1];
				this->regs->filt02_bpm_y[0] = cptr[2];
				this->regs->filt02_bpm_y[1] = cptr[3];
			} else if (chan == 1) {
				this->regs->filt13_bpm_x[0] = cptr[0];
				this->regs->filt13_bpm_x[1] = cptr[1];
				this->regs->filt13_bpm_y[0] = cptr[2];
				this->regs->filt13_bpm_y[1] = cptr[3];
			} else {
				print("Filter ID not valid\n\r");
			}
		}
		break;
	case 'c': //reset LOS counters
		//read-modify-write
		data = this->regs->reset;
		this->regs->reset = data | REG_RST_LCNT_ALL; //reset
		this->regs->reset = data & (~REG_RST_LCNT_ALL); //release reset
		print("Loss-of-Sync counters reset\n\n\r");
		break;
//	case 'd': //reset CRC ERROR counter
//		//read-modify-write
//		data = this->reg[REG_RST];
//		this->reg[REG_RST] = data | REG_RST_CRC_ECNT; //reset
//		this->reg[REG_RST] = data & (~REG_RST_CRC_ECNT); //release reset
//		print("CRC error counter reset\n\n\r");
//		break;
	case 'h': //set histogram parameters
		if (argc != 4) {
			print("\n\rUSAGE:\n\r");
			print("    switch h CENTER WIDTH\n\r");
			print("    WIDTH: 0x1 to 0x10 (hex32)\n\r");
			print("    CENTER: any value (hex32)\n\r");
			print("\n\r");
		} else {
			data = strtol(argv[2], NULL, 0);
			chan = strtol(argv[3], NULL, 0);
			xil_printf("\n\rSetting histogram center to %d and width to %d\n\r", data, chan);
			this->ddr_mem->ipt_histo_center_bin = data;
			this->ddr_mem->ipt_histo_hwidth = chan;
		}
		break;
	case 'i': /* init */
		data = 0x00640065;
		cptr = (unsigned char*) &data;
		chan = 0;
		xil_printf("\n\rSetting BPM IDs for channel %d to (XXYY):\n\r", chan);
		xil_printf("    0x%02X, 0x%02X, 0x%02X, 0x%02X\n\r", \
				cptr[0], cptr[1], cptr[2], cptr[3]);
		this->regs->filt13_bpm_x[0] = cptr[0];
		this->regs->filt13_bpm_x[1] = cptr[1];
		this->regs->filt13_bpm_y[0] = cptr[2];
		this->regs->filt13_bpm_y[1] = cptr[3];

		chan = 1;
		data = 0x96979899;
		xil_printf("\n\rSetting BPM IDs for channel %d to:\n\r", chan);
		xil_printf("    0x%02X, 0x%02X, 0x%02X, 0x%02X\n\r", \
				cptr[0], cptr[1], cptr[2], cptr[3]);
		this->regs->filt02_bpm_x[0] = cptr[0];
		this->regs->filt02_bpm_x[1] = cptr[1];
		this->regs->filt02_bpm_y[0] = cptr[2];
		this->regs->filt02_bpm_y[1] = cptr[3];

		xil_printf("Resetting error counters...\n\r");
		//read-modify-write
		data = this->regs->reset;
		this->regs->reset = data | REG_RST_LCNT_ALL | REG_RST_CRC_ECNT; //assert resets
		this->regs->reset = data & (~REG_RST_LCNT_ALL) & (~REG_RST_CRC_ECNT); //release resets
		break;
	case 'k': /* SET LOOPBACK */
		if (argc < 3) {
			print("\n\rUSAGE:\n\r");
			print("    switch k CHANNEL MODE\n\r");
			print("    MODE: loopback mode\n\r");
			print("        0: no loopback\n\r");
			print("        1: near-end PCS\n\r");
			print("        2: near-end PMA\n\r");
			print("        4: far-end PMA\n\r");
			print("        6: far-end PCS\n\r");
			print("\n\r");
		} else {
			chan = atoi(argv[2]);
			data = strtol(argv[3], NULL, 0);
			if (ibfb_switch_set_loopback(this, chan, (char) data))
				print("Bad paramaters\n\r");
		}
		break;
	case 'p':
		if (argc < 3) {
			print("\n\rUSAGE:\n\r");
			print("    switch p PING_EN\n\r");
			print("    PING_EN: ping enable mask (4 bit, 0:3)\n\r");
			print("\n\r");
		} else {
			chan = atoi(argv[2]);
			if (ibfb_switch_set_ping_en(this, chan)) {
				print("Bad mask value\n\r");
			} else {
				xil_printf("Set mask to 0x%X\n\r", chan);
			}
		}
		break;
	case 's':
		ibfb_switch_print_stats(this);
		break;
	case 't':
		print("Sending trigger\n");
		data = this->regs->reset;
		this->regs->reset = data & ~(REG_RST_FILT13 | REG_RST_FILT02);
		this->regs->reset = data |  (REG_RST_FILT13 | REG_RST_FILT02);
		this->regs->reset = data & ~(REG_RST_FILT13 | REG_RST_FILT02);
		break;
	case 'x':
		xil_printf("ShotID: %d\n\r", this->ddr_mem->xfelTimParams.shotID);
		for (i=0;i<3;i++) {
			xil_printf("Train %d: %d, %d, %d, %d\n\r", i,
					this->ddr_mem->xfelTimParams.trains[i].start,
					this->ddr_mem->xfelTimParams.trains[i].duration,
					this->ddr_mem->xfelTimParams.trains[i].increment,
					this->ddr_mem->xfelTimParams.trains[i].bunches);
		}
		xil_printf("Invalid commands: %d\n\r", this->ddr_mem->xfelTimParams.invalidCmd);
		xil_printf("Invalid identifiers: %d\n\r", this->ddr_mem->xfelTimParams.invalidIdent);
		xil_printf("Address: 0x%08X\n\r", &this->ddr_mem->xfelTimParams);
		break;
	case 'z':
		this->ddr_mem->reset_stats = 1;
		break;
	default: /* HELP */
		xil_printf("\n\rIBFB Switch Commands (Version %d.%d, FW 0x%X)\n\r", VMAJ, VMIN, this->reg[31]);
		print("    h - Print this help\n\r");
		print("    0 - Reset Switch (MGTs, Router, Filters)\n\r");
		print("    1 - Print RAW register map\n\r");
		print("    a - Print Switch's status\n\r");
		print("    b - Set allowed BPM IDs\n\r");
		print("    c - Reset LOS counters\n\r");
		print("    d - Reset CRC ERRORS counter\n\r");
		print("    h - set delay histogram parametersr\n\r");
		print("    i - Self initialize (debug)\n\r");
		print("    k - Set MGT loopback mode\n\r");
		print("    p - Set PING enable\n\r");
		print("    s - Print Packet and PING statistics\n\r");
		print("    t - send trigger (reset packet filter)\n\r");
		print("    z - reset QDR statistics\n\r");
		print("\n\rChannel Numbering (9:0): BPM(3,2,1,0); P0(1,0); QSFP(3,2,1,0)\n\r");
		print("\n\r");

	}

	return 0;
}

/********************************************************************************************/


int ibfb_compute_filt_stats(struct structIBFBSwitch *this, unsigned char sfp, unsigned int np) {

	int i;
	unsigned char bpm_id[4], filter_id, qdr_id, first[4];
	unsigned int  n_pkt, pkt_bpm, current_bpm_id;
	unsigned int  this_time[5], last_time[5], bpm_cnt[5], histo_cnt[5][2*IBFB_IPT_HISTO_HWIDTH_MAX+1];
	int           ipt, ipt_min[5], ipt_max[5], current_histo_id, histo_center_bin, histo_first_bin, histo_hwidth, last_index;

	//data for SFP2 is stored in QDR page 1, data for SFP1 is stored in QDR page 2
	switch (sfp) {
	case 0:
		qdr_id    = 0;
		filter_id = 0; //filter02
		break;
	case 1:
		qdr_id    = 2;
		filter_id = 1; //filter13
		break;
	case 2:
		qdr_id    = 1;
		filter_id = 0; //filter02
		break;
	case 3:
		qdr_id    = 3;
		filter_id = 1; //filter13
		break;
	default: //sfp parameter not valid
		return -1;
	}


	//reset bunch-related stats
	memset(bpm_cnt,   0, sizeof(bpm_cnt));
	memset(histo_cnt, 0, sizeof(histo_cnt));
	memset(first,     1, sizeof(first));
	for(i=0; i<5; i++) {
		ipt_min[i] = 0x7FFFFFFF;
		ipt_max[i] = 0x80000000;
	}

	//Compute histogram parameters
	histo_hwidth     = (int) this->ddr_mem->ipt_histo_hwidth;     //half-width: number of bins left/right of central bin
	if (histo_hwidth > IBFB_IPT_HISTO_HWIDTH_MAX) {
		histo_hwidth                    = IBFB_IPT_HISTO_HWIDTH_MAX;
		this->ddr_mem->ipt_histo_hwidth = IBFB_IPT_HISTO_HWIDTH_MAX; //correct also stored parameter
	}
	histo_center_bin = (int) this->ddr_mem->ipt_histo_center_bin; //ipt used as central bin in histogram
	histo_first_bin  = histo_center_bin - histo_hwidth;           //ipt used as 1st bin in histogram
	last_index       = 2*histo_hwidth;							  //index of last bin

	//get number of packets and BPM IDs
	if (np) {
		n_pkt = np;
	} else {
		n_pkt = this->regs->sfp_in_packets[qdr_id]; //also packet numbers are ordered as data in QDR
		if (filter_id) { //filter13
			bpm_id[0] = this->regs->filt13_bpm_x[0];
			bpm_id[1] = this->regs->filt13_bpm_x[1];
			bpm_id[2] = this->regs->filt13_bpm_y[0];
			bpm_id[3] = this->regs->filt13_bpm_y[1];
		} else { //filter02
			bpm_id[0] = this->regs->filt02_bpm_x[0];
			bpm_id[1] = this->regs->filt02_bpm_x[1];
			bpm_id[2] = this->regs->filt02_bpm_y[0];
			bpm_id[3] = this->regs->filt02_bpm_y[1];
		}
	}

	//process packets
	for (i=0; i<n_pkt; i++) {

		/* compute number of packets per BPM */
		//get BPM_ID for current packet
		pkt_bpm = (this->qdr_mem->sfp_rx[qdr_id].control[i] >> 16) & 0xFF;
		//check whether current ID matches with allowed ones
		if (pkt_bpm == bpm_id[0]) {
			current_bpm_id = 0; //X0
		} else if (pkt_bpm == bpm_id[1]) {
			current_bpm_id = 1; //X1
		} else if (pkt_bpm == bpm_id[2]) {
			current_bpm_id = 2; //Y0
		} else if (pkt_bpm == bpm_id[3]) {
			current_bpm_id = 3; //Y1
		} else {
			current_bpm_id = 4; //BAD ID
		}
		//increment BPM_ID counter
		bpm_cnt[current_bpm_id]++;

		//compute histogram
		//  0 | ... | N-2 | N-1 |   N    | N+1 | N+2 | ... | 2N
		// -N | ... | -2  | -1  | CENTER |  +1 |  +2 | ... | +N
		if (first[current_bpm_id]) {
			//first packet for current BPM ID: reset "first" flag and save timestamp
			first[current_bpm_id] = 0;
			last_time[current_bpm_id] = this->qdr_mem->sfp_rx[qdr_id].timestamp[i];
		} else {
			this_time[current_bpm_id] = this->qdr_mem->sfp_rx[qdr_id].timestamp[i];    //store current timestamp (avoid reading twice from QDR)
			ipt                       = (int) (this_time[current_bpm_id] - last_time[current_bpm_id]); //compute intra-packet time
			ipt_max[current_bpm_id]   = (ipt>ipt_max[current_bpm_id])?ipt:ipt_max[current_bpm_id]; //update max delay value for current BPM ID
			ipt_min[current_bpm_id]   = (ipt<ipt_min[current_bpm_id])?ipt:ipt_min[current_bpm_id]; //update min delay value for current BPM ID
			last_time[current_bpm_id] = this_time[current_bpm_id];                     //store current time to be used as last time for next computation

			current_histo_id = (ipt - histo_first_bin); //current IPT corresponds to this histogram bin
			if (current_histo_id < 0) { //below minimum value: increment leftmost bin
				histo_cnt[current_bpm_id][0]++;
			} else if (current_histo_id > last_index) { //above maximum value: increment last bin
				histo_cnt[current_bpm_id][last_index]++;
			} else {
				histo_cnt[current_bpm_id][current_histo_id]++;
			}
		}
	} //for cycle

	//store data into DDR
	for(i=0; i<5; i++) {
		this->ddr_mem->sfp_bpm_cnt[sfp][i] = bpm_cnt[i];
		this->ddr_mem->ipt_max[sfp][i] = ipt_max[i];
		this->ddr_mem->ipt_min[sfp][i] = ipt_min[i];
	}

	for (i=0; i<=last_index; i++) {
		this->ddr_mem->sfp_ipt_histo[sfp][0][i] = histo_cnt[0][i];
		this->ddr_mem->sfp_ipt_histo[sfp][1][i] = histo_cnt[1][i];
		this->ddr_mem->sfp_ipt_histo[sfp][2][i] = histo_cnt[2][i];
		this->ddr_mem->sfp_ipt_histo[sfp][3][i] = histo_cnt[3][i];
		this->ddr_mem->sfp_ipt_histo[sfp][4][i] = histo_cnt[4][i];
	}

	return 0;
}

int ibfb_switch_update_bunch_trains(struct structIBFBSwitch *this) {

	struct structXFELTIMParams *tim = &this->ddr_mem->xfelTimParams;

	if (this->bpm_sel == IBFB_BPM1_FPGA) {
		if (tim->trains[0].bunches) { // SASE1
			this->regs->filt02_bucket_start = tim->trains[0].start/2;
			this->regs->filt02_bucket_stop = tim->trains[0].start/2 + tim->trains[0].increment/2 * (tim->trains[0].bunches-1);
		}
		else {
			this->regs->filt02_bucket_start = IBFB_CTRL_XFEL_BUCKET_NUMBER;
			this->regs->filt02_bucket_stop = IBFB_CTRL_XFEL_BUCKET_NUMBER;
		}
		if (tim->trains[1].bunches) { // SASE2
			this->regs->filt13_bucket_start = tim->trains[1].start/2;
			this->regs->filt13_bucket_stop = tim->trains[1].start/2 + tim->trains[1].increment/2 * (tim->trains[1].bunches-1);
		}
		else {
			this->regs->filt13_bucket_start = IBFB_CTRL_XFEL_BUCKET_NUMBER;
			this->regs->filt13_bucket_stop = IBFB_CTRL_XFEL_BUCKET_NUMBER;
		}
	}
	else { // BPM2_FPGA
		if (tim->trains[2].bunches) { // SASE3
			this->regs->filt02_bucket_start = tim->trains[2].start/2;
			this->regs->filt02_bucket_stop = tim->trains[2].start/2 + tim->trains[2].increment/2 * (tim->trains[2].bunches-1);
		}
		else {
			this->regs->filt02_bucket_start = IBFB_CTRL_XFEL_BUCKET_NUMBER;
			this->regs->filt02_bucket_stop = IBFB_CTRL_XFEL_BUCKET_NUMBER;
		}
		// always all packets from collimator BPM
		this->regs->filt13_bucket_start = 0;
		this->regs->filt13_bucket_stop = IBFB_CTRL_XFEL_BUCKET_NUMBER-1;
	}

	return 0;
}

int ibfb_switch_xfeltim_int(struct structIBFBSwitch *this) {

	this->XFELTIM.parse_frames(&this->XFELTIM);
	ibfb_switch_update_bunch_trains(this);

	return 0;
}

int ibfb_switch_hw_int(struct structIBFBSwitch *this) {

	unsigned int start, xtime;

	this->ddr_mem->interrupt_counter++;

	start = this->regs->timer;

	if (this->ddr_mem->reset_stats) {
		this->ddr_mem->filt02_bad_bpm_cnt  = 0;
		this->ddr_mem->filt13_bad_bpm_cnt  = 0;
		this->ddr_mem->interrupt_counter   = 0;
		this->ddr_mem->last_execution_time = 0;
		this->ddr_mem->min_execution_time  = 0xFFFFFFFF;
		this->ddr_mem->max_execution_time  = 0;

		this->ddr_mem->reset_stats = 0;
	} else if ((this->qdr_status == 0) && (this->ddr_mem->stats_ena == 1)) {
		if (this->regs->filt02_bad_bpm_id) {
			this->ddr_mem->filt02_bad_bpm_cnt++;
		}
		if (this->regs->filt13_bad_bpm_id) {
			this->ddr_mem->filt13_bad_bpm_cnt++;
		}
			ibfb_compute_filt_stats(this, 0, 0);
			ibfb_compute_filt_stats(this, 1, 0);
			ibfb_compute_filt_stats(this, 2, 0);
			ibfb_compute_filt_stats(this, 3, 0);
	}

	/*
	 * When post-processing is finished, generate interrupt,
	 * the register is cleared by the control system or a new trigger
	 */
	this->regs->ctrl_sys_int = 1;

	xtime = (this->regs->timer - start);
	if (xtime > this->ddr_mem->max_execution_time) {
		this->ddr_mem->max_execution_time = xtime;
	} else if (xtime < this->ddr_mem->min_execution_time) {
		this->ddr_mem->min_execution_time = xtime;
	}
	this->ddr_mem->last_execution_time = xtime;

	return 0;
}


int ibfb_ctrl_init_functions(struct structIBFBSwitch *this) {

	// init functions
	this->functions->trg_mode = 0;
	this->functions->trg_source = 0;
	this->functions->bunch_delay = 32767;
	this->functions->bunch_number = 5;
	this->functions->bunch_space = 1;

	return 0;
}

int ibfb_switch_init(struct structIBFBSwitch *this) {

	// reset all GTX
	ibfb_switch_gtx_init(this);

	// set routing tables
	if (this->bpm_sel) {		// BPM2 FPGA
		//this->regs->router_out_ena = IBFB_SWITCH_BPM2_ROUTER_OUTPUTS;
		this->regs->xrouter_table       = IBFB_SWITCH_BPM2_XROUTER_TABLE;
		this->regs->yrouter_table       = IBFB_SWITCH_BPM2_YROUTER_TABLE;
		this->regs->filt02_bucket_start = IBFB_CTRL_XFEL_BUCKET_NUMBER-1;
		this->regs->filt02_bucket_stop  = IBFB_CTRL_XFEL_BUCKET_NUMBER-1;
		this->regs->filt13_bucket_start = 0;
		this->regs->filt13_bucket_stop  = IBFB_CTRL_XFEL_BUCKET_NUMBER-1;
	} else {					// BPM1 FPGA
		//this->regs->router_out_ena = IBFB_SWITCH_BPM1_ROUTER_OUTPUTS;
		this->regs->xrouter_table       = IBFB_SWITCH_BPM1_XROUTER_TABLE;
		this->regs->yrouter_table       = IBFB_SWITCH_BPM1_YROUTER_TABLE;
		this->regs->filt02_bucket_start = IBFB_CTRL_XFEL_BUCKET_NUMBER-1;
		this->regs->filt02_bucket_stop  = IBFB_CTRL_XFEL_BUCKET_NUMBER-1;
		this->regs->filt13_bucket_start = IBFB_CTRL_XFEL_BUCKET_NUMBER-1;
		this->regs->filt13_bucket_stop  = IBFB_CTRL_XFEL_BUCKET_NUMBER-1;
	}

	//DDR memory init
	this->ddr_mem->reset_stats          = 0;
    this->ddr_mem->ipt_histo_center_bin = IBFB_IPT_HISTO_CENTER; //default value
    this->ddr_mem->ipt_histo_hwidth     = IBFB_IPT_HISTO_HWIDTH; //default value
	this->ddr_mem->interrupt_counter    = 0;
	this->ddr_mem->last_execution_time  = 0;
	this->ddr_mem->min_execution_time   = 0xFFFFFFFF;
	this->ddr_mem->max_execution_time   = 0;
	this->ddr_mem->filt02_bad_bpm_cnt   = 0;
	this->ddr_mem->filt13_bad_bpm_cnt   = 0;

	memset(this->ddr_mem->sfp_bpm_cnt,   0, sizeof(this->ddr_mem->sfp_bpm_cnt));
	memset(this->ddr_mem->sfp_ipt_histo, 0, sizeof(this->ddr_mem->sfp_ipt_histo));
	memset(this->ddr_mem->ipt_min,       0, sizeof(this->ddr_mem->ipt_min));
	memset(this->ddr_mem->ipt_max,       0, sizeof(this->ddr_mem->ipt_max));

	this->ddr_mem->stats_ena = 1;

	ibfb_ctrl_init_functions(this);
	ibfb_ctrl_update_timing(this);

	return 0;
}

/*
 * Initialize IBFB data structure
 */
int structIBFBSwitch_new(
		struct structIBFBSwitch *this,
		unsigned int switch_reg_addr,
		unsigned int qdr2_addr,
		unsigned int ddr2_addr,
		unsigned int func_reg_addr,
		unsigned int func_mem_addr,
		unsigned int func_mem_size,
		unsigned int xfeltim_reg_addr,
		unsigned int xfeltim_mem_addr) {


	structFunctionController_new(&this->FunctionController, func_reg_addr, func_mem_addr, func_mem_size);
	structXFELTIM_new(&this->XFELTIM, xfeltim_reg_addr, xfeltim_mem_addr);

	this->FunctionController.userCallback = ibfb_ctrl_function_process;
	this->FunctionController.userObject = this;
	this->FunctionController.interruptInit(&this->FunctionController, IBFB_CTRL_FUNC_NUM_OF_INT_REGS);

	// properties
	this->regs = (struct structIBFBSwitchRegs *)switch_reg_addr;
	this->functions = (struct structIBFBFunctions *)func_mem_addr;
	this->reg = (volatile unsigned int *)switch_reg_addr;
	this->qdr_mem = (struct structIBFBMemoryQDR *)qdr2_addr;
	this->ddr_mem = (struct structIBFBMemoryDDR *)ddr2_addr;
	this->XFELTIM.timParams = (struct structXFELTIMParams *)&this->ddr_mem->xfelTimParams;

	// methods
	this->ibfb_cmd = ibfb_switch_ibfb_cmd;
	this->init = ibfb_switch_init;
	this->hw_int = ibfb_switch_hw_int;
	this->xfeltim_int = ibfb_switch_xfeltim_int;

	//clean memory
	memset(&this->ddr_mem->xfelTimParams, 0, 256);

	return 0;
}



