/*
 * ibfb_switch.h
 *
 *  Created on: 08.01.2016
 *      Author: koprek_w
 */

#ifndef IBFB_SWITCH_H_
#define IBFB_SWITCH_H_

#include <stdio.h>
#include "func_ctrl_v1_01_a.h"
#include "xfel_tim_bpm_mem.h"

#define IBFB_BPM1_FPGA		0
#define IBFB_BPM2_FPGA		1

#define IPT_MIN(x) (x==0x7FFFFFFF)?0:x
#define IPT_MAX(x) (x==0x80000000)?0:x

#define IBFB_K_SOP 0xFB
#define IBFB_K_EOP 0xFD
#define IBFB_K_BAD 0x5C

//#define IBFB_SWITCH_NUM_OF_TILES		5
//#define IBFB_SWITCH_TILE_QSFP13			0
//#define IBFB_SWITCH_TILE_QSFP24			1
//#define IBFB_SWITCH_TILE_P0				2
//#define IBFB_SWITCH_TILE_BPM01			3
//#define IBFB_SWITCH_TILE_BPM23			4

#define IBFB_CTRL_FUNC_NUM_OF_INT_REGS		27				// number of first registers which have enabled interrupts
#define IBFB_CTRL_XFEL_BUCKET_SPACE			48				// 48 clock cycles of 216.(6) MHz
#define IBFB_CTRL_XFEL_BUCKET_NUMBER		2708			// E-XFEL it is a 5416 packets divided by 2


#define IBFB_SWITCH_BPM1_XROUTER_TABLE		0x2A			// Filt02->P0, Filt13->P0, BPM->P0
#define IBFB_SWITCH_BPM1_YROUTER_TABLE		0x2A			// Filt02->P0, Filt13->P0, BPM->P0
#define IBFB_SWITCH_BPM2_XROUTER_TABLE		0x14			// Filt02->BPM, Filt13->BPM
#define IBFB_SWITCH_BPM2_YROUTER_TABLE		0x14			// Filt02->BPM, Filt13->BPM

#define IBFB_SWITCH_QDR_NPACKETS 0x4000 //16K packets

//loopback codes
#define LB_NONE   0x00 //normal operation
#define LB_NE_PCS 0x01 //near-end PCS loopback
#define LB_NE_PMA 0x02 //near-end PMA loopback
#define LB_FE_PMA 0x04 //far-end PMA loopback
#define LB_FE_PCS 0x06 //far-end PCS loopback

#define NREGS 38

#define		REG_RST_CRC_ECNT  0x80000000
#define		REG_RST_ALL       0xBFF03FFF
#define		REG_RST_LCNT_ALL  0x3FF00000
#define		REG_RST_FILT13    0x00000400
#define		REG_RST_FILT02    0x00000800

struct structIBFBFunctions{						//		addr		size =
	volatile unsigned int pad1;					//	  0x0000		   4
	volatile unsigned char trg_source;			//	  0x0004		   1
	volatile unsigned char trg_mode;			//	  0x0005		   1
	volatile unsigned char pad2;				//    0x0006           1
	volatile unsigned char pad3;				//	  0x0007		   1
	volatile unsigned int bunch_delay;			//	  0x0008		   4
	volatile unsigned short bunch_number;		//	  0x000C		   2
	volatile unsigned short bunch_space;		//	  0x000E		   2
};

struct structIBFBSwitchRegs{						//		addr		size =
	volatile unsigned int   reset;					//	  0x0000-03 	   4
	volatile unsigned char loopback_bpm23;			//	  0x0004		   1
	volatile unsigned char loopback_bpm01;			//	  0x0005		   1
	volatile unsigned char loopback_qsfp23;			//	  0x0006		   1
	volatile unsigned char loopback_qsfp01;			//	  0x0007		   1
	//volatile unsigned char router_out_ena;		//	  0x0008		   1 //REMOVED FROM FW
	volatile unsigned char  pad8;			    	//	  0x0008		   1
	volatile unsigned char  xrouter_table;			//	  0x0009		   1
	volatile unsigned char  yrouter_table;			//	  0x000A		   1
	volatile unsigned char loopback_p0;				//	  0x000B		   1
	//volatile unsigned int pad0_2[4];				//	  0x000C		  16
	//volatile unsigned char  padC[4];				//	  0x000C-F		   4
	volatile unsigned char  mgt_b23_status;			//	  0x000C		   1
	volatile unsigned char  mgt_b01_status;			//	  0x000D		   1
	volatile unsigned char  mgt_q02_status;			//	  0x000E		   1
	volatile unsigned char  mgt_q13_status;			//	  0x000F		   1
	volatile unsigned char  k_sop;					//	  0x0010		   1
	volatile unsigned char  k_eop;					//	  0x0011		   1
	volatile unsigned char  router_out_err;			//	  0x0012		   1
	volatile unsigned char  mgt_p0_status;			//	  0x0013		   1
	volatile unsigned char  pad14;	 			    //	  0x0014		   1
	volatile unsigned char  rxsync_MSB;   			//	  0x0015		   1
	volatile unsigned char  rxsync_LSB;   			//	  0x0016		   1
	volatile unsigned char  pad17;	 				//	  0x0017		   1
	volatile unsigned int   ctrl_sys_int;	 		//	  0x0018-1B		   4
	volatile unsigned char  filt13_bpm_y[2];		//    0x001C-1D		   2
	volatile unsigned char  filt13_bpm_x[2];		//    0x001E-1F		   2
	volatile unsigned char  filt02_bpm_y[2];		//    0x0020-21		   2
	volatile unsigned char  filt02_bpm_x[2];		//    0x0022-23		   2
	//volatile unsigned int pad1_2[6];				//	  0x0024		  24
	volatile unsigned short los_cnt_qsfp1;			//    0x0024-25		   2
	volatile unsigned short los_cnt_qsfp0;			//    0x0026-27		   2
	volatile unsigned short los_cnt_qsfp3;			//    0x0028-29		   2
	volatile unsigned short los_cnt_qsfp2;			//    0x002A-2B		   2
	volatile unsigned short los_cnt_bpm1;			//    0x002C-2D		   2
	volatile unsigned short los_cnt_bpm0;			//    0x002E-2F		   2
	volatile unsigned short los_cnt_bpm3;			//    0x0030-31		   2
	volatile unsigned short los_cnt_bpm2;			//    0x0032-33		   2
	volatile unsigned short los_cnt_p01;			//    0x0034-35		   2
	volatile unsigned short los_cnt_p00;			//    0x0036-37		   2
	volatile unsigned int   timer;					//	  0x0038-3B		   4
	volatile unsigned char  pad3C;				    //    0x003C		   1
	volatile unsigned char trg_source;				//    0x003D		   1
	volatile unsigned char trg_mode;				//    0x003E		   1
	volatile unsigned char trg_enabled;				//    0x003F		   1
	volatile unsigned int   bunch_delay;			//    0x0040-43		   4
	volatile unsigned short bucket_space;			//    0x0044-45		   2
	volatile unsigned short bucket_number;			//    0x0046-47		   2
	volatile unsigned char  pad48[3];				//    0x0048-4A		   3
	volatile unsigned char trg_rate;				//    0x004B		   1
	volatile unsigned int   trg_once;		    	//    0x004C-4F		   4
	volatile unsigned char  pad50[2];				//    0x0050-51		   2
	volatile unsigned char read_ready;				//    0x0052		   1
	volatile unsigned char trg_ext_missing;			//    0x0053		   1
	//volatile unsigned int pad5[7];				//    0x0054		  28
	volatile unsigned short sfp_in_packets[4];		//    0x0054-5B		   8 //SFP0,2,1,3
	volatile unsigned short filt02_discard_x;		//    0x005C-5D		   2
	volatile unsigned short filt02_discard_y;		//    0x005E-5F		   2
	volatile unsigned short filt13_discard_x;		//    0x0060-61		   2
	volatile unsigned short filt13_discard_y;		//    0x0062-63		   2
	volatile unsigned char  filt02_bad_bpm_id;	    //    0x0064		   1
	volatile unsigned char  pad65;	    			//    0x0065		   1
	volatile unsigned char  filt13_bad_bpm_id;	    //    0x0066		   1
	volatile unsigned char  pad67;	    			//    0x0067		   1
	volatile unsigned short filt02_passed_x;		//    0x0068-69		   2
	volatile unsigned short filt02_passed_y;		//    0x006A-6B		   2
	volatile unsigned short filt13_passed_x;		//    0x006C-6D		   2
	volatile unsigned short filt13_passed_y;		//    0x006E-6F		   2
	volatile unsigned short filt02_bucket_start;	//	  0x0070-71		   2
	volatile unsigned short filt02_bucket_stop;		//	  0x0072-73		   2
	volatile unsigned short filt13_bucket_start;	//	  0x0074-75		   2
	volatile unsigned short filt13_bucket_stop;		//	  0x0076-77		   2
	volatile unsigned int   pad78;					//	  0x0078-7B		   4
	volatile unsigned int   fw_serial;				//	  0x007C-7F		   4
	volatile unsigned char  ping_en_sfp0;			//	  0x0080		   1
	volatile unsigned char  ping_en_sfp1;			//	  0x0081		   1
	volatile unsigned char  ping_en_sfp2;			//	  0x0082		   1
	volatile unsigned char  ping_en_sfp3;			//	  0x0083		   1
	volatile unsigned char  ping_rx_sfp0;			//	  0x0084		   1
	volatile unsigned char  ping_rx_sfp1;			//	  0x0085		   1
	volatile unsigned char  ping_rx_sfp2;			//	  0x0086		   1
	volatile unsigned char  ping_rx_sfp3;			//	  0x0087		   1
	volatile unsigned int   ping_latency_sfp0;		//	  0x0088-8B		   4
	volatile unsigned int   ping_latency_sfp1;		//	  0x008C-8F		   4
	volatile unsigned int   ping_latency_sfp2;		//	  0x0090-93		   4
	volatile unsigned int   ping_latency_sfp3;		//	  0x0094-97		   4
};

//data received from one filter as stored in QDR (16K packets, 4*32bit per packet)
struct structIBFBGTXChannel {							// 		addr	size = 256k bytes
	unsigned int timestamp[IBFB_SWITCH_QDR_NPACKETS];	//	 0x00000	64k
	unsigned int control[IBFB_SWITCH_QDR_NPACKETS];		//   0x10000	64k
	float 		 xpos[IBFB_SWITCH_QDR_NPACKETS];		//   0x20000	64k
	float 		 ypos[IBFB_SWITCH_QDR_NPACKETS];		//   0x30000	64k
};

//QDR memory content
struct structIBFBMemoryQDR {				// 		addr	size = 1048576 bytes
	struct structIBFBGTXChannel sfp_rx[4];	//  0x000000	256k //stored as 0,2,1,3
};

//Data stored in DDR2 memory
#define IBFB_IPT_HISTO_HWIDTH_MAX 16
#define IBFB_IPT_HISTO_HWIDTH 10  //DEFAULT: Intra-packet-time Histogram half-width
#define IBFB_IPT_HISTO_CENTER 49 //DEFAULT: Intra-packet-time Histogram Center Bin

struct structIBFBMemoryDDR {  											// 		addr	size = 1048576 bytes
	volatile unsigned char  reset_stats;                              			//0x00000000 //set to 1 to make ISR reset all statistics
	volatile unsigned char  ipt_histo_hwidth;		                 			//0x00000001
	volatile unsigned short ipt_histo_center_bin;		             			//0x00000002-0x00000003
	volatile unsigned int   interrupt_counter;						 			//0x00000004-0x00000007
	volatile unsigned int   last_execution_time;						 			//0x00000008-0x0000000B
	volatile unsigned int   max_execution_time;                       			//0x0000000C-0x0000000F
	volatile unsigned int   min_execution_time;                       			//0x00000010-0x00000013
	volatile unsigned int   filt02_bad_bpm_cnt;                       			//0x00000014-0x00000017
	volatile unsigned int   filt13_bad_bpm_cnt;                       			//0x00000018-0x0000001B
	volatile unsigned int   sfp_bpm_cnt[4][5];                        			//0x0000001C-0x0000002F //[SFP][ID(XXYY)]
	volatile unsigned int   sfp_ipt_histo[4][5][2*IBFB_IPT_HISTO_HWIDTH_MAX+1];
	volatile int            ipt_max[4][5];
	volatile int            ipt_min[4][5];
	volatile unsigned char  stats_ena;
	volatile unsigned char  pad[3];
	volatile unsigned char  pad4096[1184];										//0x00000B60   1184
	struct structXFELTIMParams xfelTimParams;									//0x00001000    256
};

struct structIBFBSwitch {
	struct structFunctionController FunctionController;
	struct structIBFBFunctions *functions;
	struct structIBFBSwitchRegs *regs;
	struct structXFELTIM XFELTIM;
	volatile unsigned int *reg;
	struct structIBFBMemoryQDR *qdr_mem;
	struct structIBFBMemoryDDR *ddr_mem;
	volatile unsigned int bpm_sel;
	volatile unsigned int qdr_status;
	int (*ibfb_cmd)(void *object, int argc, char *argv[]);
	int (*init)(struct structIBFBSwitch *this);
	int (*hw_int)(struct structIBFBSwitch *this);
	int (*xfeltim_int)(struct structIBFBSwitch *this);
};


int structIBFBSwitch_new(
		struct structIBFBSwitch *this,
		unsigned int switch_reg_addr,
		unsigned int qdr2_addr,
		unsigned int ddr2_addr,
		unsigned int func_reg_addr,
		unsigned int func_mem_addr,
		unsigned int func_mem_size,
		unsigned int xfeltim_reg_addr,
		unsigned int xfeltim_mem_addr);



#endif /* IBFB_SWITCH_H_ */
