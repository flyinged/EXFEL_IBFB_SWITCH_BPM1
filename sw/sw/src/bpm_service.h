/*
 * gpac2_bpm_service_v1_00_a.h
 *
 *  Created on: 17.10.2013
 *      Author: koprek_w
 */

#ifndef GPAC2_BPM_SERVICE_V1_00_A_H_
#define GPAC2_BPM_SERVICE_V1_00_A_H_

#include <stdio.h>
#include <string.h>


#define SERVICE_LED_1_RED_MASK			0x80000000
#define SERVICE_LED_2_RED_MASK			0x40000000

#define SERVICE_INIT_ERR_FL_IDLE		0x00000001
#define SERVICE_INIT_ERR_DCM_LOCK		0x00000002
#define SERVICE_INIT_ERR_ADC_TEST		0x00000004
#define SERVICE_INIT_ERR_DDR2_SYNC		0x00000008
#define SERVICE_INIT_ERR_QDR2_SYNC		0x00000010
#define SERVICE_INIT_ERR_BP_BRIDGE		0x00000020
//#define SERVICE_INIT_ERR_TEST			0x00000040
//#define SERVICE_REG_VER_YEAR			0x00000004
//#define SERVICE_REG_VER_MONTH			0x00000006
//#define SERVICE_REG_VER_DAY 			0x00000007
//#define SERVICE_REG_VER_HOUR			0x00000008
//#define SERVICE_REG_VER_MINUTE			0x00000009
//#define SERVICE_REG_INIT_ERR_ADDR		0x00000024

/* Data declaration */
/* Output of __DATE__ : */
/* Jan  1 2015 */
/* Feb  1 2015 */
/* Mar  1 2015 */
/* Apr  1 2015 */
/* May  1 2015 */
/* Jun  1 2015 */
/* Jul  1 2015 */
/* Aug  1 2015 */
/* Sep  1 2015 */
/* Oct  1 2015 */
/* Nov  1 2015 */
/* Dec  1 2015 */
/* 0123456789A */
#define DATE_YEAR (((__DATE__[ 7] - '0') * 1000) + ((__DATE__[ 8] - '0') * 100) + ((__DATE__[ 9] - '0') * 10) + (__DATE__[10] - '0'))
#define DATE_MONTH (__DATE__[ 0] == 'J' && __DATE__[ 1] == 'a' && __DATE__[ 2] == 'n' ?  1 :\
                    __DATE__[ 0] == 'F' && __DATE__[ 1] == 'e' && __DATE__[ 2] == 'b' ?  2 :\
                    __DATE__[ 0] == 'M' && __DATE__[ 1] == 'a' && __DATE__[ 2] == 'r' ?  3 :\
                    __DATE__[ 0] == 'A' && __DATE__[ 1] == 'p' && __DATE__[ 2] == 'r' ?  4 :\
                    __DATE__[ 0] == 'M' && __DATE__[ 1] == 'a' && __DATE__[ 2] == 'y' ?  5 :\
                    __DATE__[ 0] == 'J' && __DATE__[ 1] == 'u' && __DATE__[ 2] == 'n' ?  6 :\
                    __DATE__[ 0] == 'J' && __DATE__[ 1] == 'u' && __DATE__[ 2] == 'l' ?  7 :\
                    __DATE__[ 0] == 'A' && __DATE__[ 1] == 'u' && __DATE__[ 2] == 'g' ?  8 :\
                    __DATE__[ 0] == 'S' && __DATE__[ 1] == 'e' && __DATE__[ 2] == 'p' ?  9 :\
                    __DATE__[ 0] == 'O' && __DATE__[ 1] == 'c' && __DATE__[ 2] == 't' ? 10 :\
                    __DATE__[ 0] == 'N' && __DATE__[ 1] == 'o' && __DATE__[ 2] == 'v' ? 11 :\
                    __DATE__[ 0] == 'D' && __DATE__[ 1] == 'e' && __DATE__[ 2] == 'c' ? 12 :\
                    0)
#define DATE_DAY   (__DATE__[ 4] == ' ' ? (__DATE__[ 5] - '0') : (((__DATE__[ 4] - '0') * 10) + (__DATE__[ 5] - '0')))

/* Output of __TIME__ : */
/* 14:30:30 */
/* 01234567 */
#define TIME_HOUR   (__TIME__[0] == ' ' ? (__TIME__[1] - '0') : (((__TIME__[0] - '0') * 10) + (__TIME__[1] - '0')))
#define TIME_MINUTE (__TIME__[3] == ' ' ? (__TIME__[4] - '0') : (((__TIME__[3] - '0') * 10) + (__TIME__[4] - '0')))


struct structBPMServiceRegs {
	volatile unsigned int fw_version;				// 0x000
	volatile unsigned int fw_year;					// 0x004
	volatile unsigned int fw_month;					// 0x008
	volatile unsigned int fw_day;					// 0x00C
	volatile unsigned int fw_hour;					// 0x010
	volatile unsigned int fw_minute;				// 0x014
	volatile unsigned int sw_year;					// 0x018
	volatile unsigned int sw_month;					// 0x01C
	volatile unsigned int sw_day;					// 0x020
	volatile unsigned int sw_hour;					// 0x024
	volatile unsigned int sw_minute;				// 0x028
	volatile unsigned int errors;					// 0x02C
	volatile unsigned char served_int;				// 0x030
	volatile unsigned char pad1[2];					// 0x031
	volatile unsigned char cpu_busy_ena;			// 0x033
	volatile unsigned int cpu_busy_time;			// 0x034
	volatile unsigned int bp_link_status;			// 0x038
	volatile unsigned int cfg_bpm_sel;				// 0x03C
	volatile unsigned char gtx_sys_diffctrl;		// 0x040
	volatile unsigned char gtx_sys_rxtx_rst;		// 0x041
	volatile unsigned char gtx_sys_rxcdr_rst;		// 0x042
	volatile unsigned char gtx_sys_loopback;		// 0x043
	volatile unsigned char gtx_bpm_diffctrl;		// 0x044
	volatile unsigned char gtx_bpm_rxtx_rst;		// 0x045
	volatile unsigned char gtx_bpm_rxcdr_rst;		// 0x046
	volatile unsigned char gtx_bpm_loopback;		// 0x047
	volatile unsigned char gtx_sysbpm_reset;		// 0x048
	volatile unsigned char gtx_sysbpm_pwrdown;		// 0x049
	volatile unsigned char pad2[2];					// 0x04A, 0x04B
	volatile unsigned int gtx_sysbpm_status;		// 0x03C
	volatile unsigned int gtx_sys_losofsync_cnt;	// 0x040
	volatile unsigned int gtx_bpm_losofsync_cnt;	// 0x044
};
struct structBPMServiceMem {
	volatile unsigned int fw_version;				// 0x0000		   4
	volatile unsigned int fw_year;					// 0x0004		   4
	volatile unsigned int fw_month;					// 0x0008		   4
	volatile unsigned int fw_day;					// 0x000C		   4
	volatile unsigned int fw_hour;					// 0x0010		   4
	volatile unsigned int fw_minute;				// 0x0014		   4
	volatile unsigned int sw_year;					// 0x0018		   4
	volatile unsigned int sw_month;					// 0x001C		   4
	volatile unsigned int sw_day;					// 0x0020		   4
	volatile unsigned int sw_hour;					// 0x0024		   4
	volatile unsigned int sw_minute;				// 0x0028		   4
};

struct structBPMService {							// addr			size = 256 bytes
	struct structBPMServiceMem *mem;
	struct structBPMServiceRegs *serviceRegs;					// 0x002C		   4
	void (*print_fw_version)(struct structBPMService *this);	// 0x0030		   4
	void (*set_init_error)(struct structBPMService *this,
			               unsigned int err);						// 0x0034		   4
	void (*init_version_registers)(struct structBPMService *this);	// 0x0038		   4
	volatile char pad1[196];										// 0x003C		 196 padding to 256 bytes
};

int structBPMService_new(struct structBPMService *this, unsigned int mem_addr, unsigned int base_addr);

#endif /* GPAC2_BPM_SERVICE_V1_00_A_H_ */
