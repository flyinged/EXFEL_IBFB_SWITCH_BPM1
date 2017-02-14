/*
 * system.h
 *
 *  Created on: 15.08.2014
 *      Author: koprek_w
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "xintc_l.h"
#include "xuartlite_l.h"
#include "xio.h"
#include "xparameters.h"
#include "shell.h"
#include "interrupt.h"
#include "bpm_service.h"
#include "ibfb_switch.h"
#include "gpac_qdr2_splb_v2_00_a.h"


#define SYS_BPM1_FPGA					0
#define SYS_BPM2_FPGA					1

//#define IBFB_FUNC_CTRL_MEM0_BASEADDR		XPAR_BPM1_FUNC_CTRL_MEM0_BASEADDR + 512

#define SYSTEM_INTC_BASEADDR				XPAR_INTC_INST_BASEADDR
#define SYSTEM_UART_BASEADDR        		XPAR_UART_INST_BASEADDR
#define SYSTEM_DAC16HL_1_ADDR     			XPAR_PLBOVERLVDS_BP_SPLB_BASEADDR + 0x2000
#define SYSTEM_DAC16HL_2_ADDR     			XPAR_PLBOVERLVDS_BP_SPLB_BASEADDR + 0x3000
#define SYSTEM_DAC16HL_ADDR_SPACE			0x00002000
#define SYSTEM_DAC16HL_REG_OFFSET			0x00000000
#define SYSTEM_DAC16HL_SPI_OFFSET			0x00000100
#define SYSTEM_DAC16HL_I2C_OFFSET			0x00001000

#define IBFB_FUNC_CTRL_MEM_SIZE				64

#define SYSTEM_DDR2_BASE_ADDR		XPAR_DDR2_SDRAM_W1D32M72R8A_5A_MEM_BASEADDR
//#define SYSTEM_QDR2_BASE_ADDR		XPAR_QDR2_SPLB_MEM0_BASEADDR

// MEMORY OFFSETS
#define SYSTEM_SHARED_DDR2_OFFSET	SYSTEM_DDR2_BASE_ADDR	+ 0x07E00000		// size
#define SYSTEM_SHARED_DDR2_SERVICE	SYSTEM_DDR2_BASE_ADDR	+ 0x07E00000 		// 256
#define SYSTEM_SHARED_DDR2_CRC32	SYSTEM_DDR2_BASE_ADDR	+ 0x07E00100		// 256

#define SYSTEM_ERROR_NO_MEMORY			-1
#define SYSTEM_ERROR_CRITICAL			1
#define SYSTEM_ERROR_NOT_CRITICAL		0

#define IBFB_FUNC_CTRL_MEM0_BASEADDR		XPAR_IBFB_FUNC_CTRL_MEM0_BASEADDR + 512
#define IBFB_SWITCH_DDR2_BASE              (XPAR_DDR2_SDRAM_W1D32M72R8A_5A_MEM_BASEADDR + 0x07E10000)

struct structSystem{
	struct structBPMService BPMService;
	struct structInterrupt Interrupt;
	struct structShell Shell;
	struct structIBFBSwitch IBFBSwitch;
	struct structQDR2 QDR2;
	void (*init_hardware)();
};


int structSystem_new(struct structSystem *this);
//struct structSystem* structSystem_new();

#endif /* SYSTEM_H_ */
