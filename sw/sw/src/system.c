/*
 * system.c
 *
 *  Created on: 15.08.2014
 *      Author: koprek_w
 */

#include "system.h"

void system_clrscr() {
	int i;

	for (i=1;i<80;i++)
		print("\n\r");

	return;
}

void system_hello(struct structSystem *this) {

	system_clrscr();

	xil_printf("GPAC 2.1, BPM%d FPGA\n\r", this->BPMService.serviceRegs->cfg_bpm_sel+1);
	print("European XFEL IBFB Switch\n\n\r");

	return;
}

void system_set_bp_addresses(struct structSystem *this) {

	//unsigned int bpm = this->BPMService->serviceRegs->cfg_bpm_sel;
	//unsigned int reg_addr = SYSTEM_DAC16HL_1_ADDR + SYSTEM_DAC16HL_ADDR_SPACE * bpm + SYSTEM_DAC16HL_REG_OFFSET;
	//unsigned int spi_addr = SYSTEM_DAC16HL_1_ADDR + SYSTEM_DAC16HL_ADDR_SPACE * bpm + SYSTEM_DAC16HL_SPI_OFFSET;
	//unsigned int i2c_addr = SYSTEM_DAC16HL_1_ADDR + SYSTEM_DAC16HL_ADDR_SPACE * bpm + SYSTEM_DAC16HL_I2C_OFFSET;

	//this->DAC16HL->init_addresses(this->DAC16HL, reg_addr, i2c_addr, spi_addr);
	//this->IBFBCtrl->DAC16HL->DAC16HL->init_addresses(this->IBFBCtrl->DAC16HL->DAC16HL, reg_addr, i2c_addr, spi_addr);

	return;
}


void system_init_hardware(struct structSystem *this) {

	int res;

    //Enable interrupts in RS232
    XUartLite_SetControlReg(SYSTEM_UART_BASEADDR, XUL_CR_ENABLE_INTR | XUL_CR_FIFO_TX_RESET);

    system_hello(this);

    print("Hardware initialization...");

    print("QDR2 memory synchronization...");
    if ((res = this->QDR2.qdr2AdjustDelay(&this->QDR2, QDR2_GPAC2_IDELAY))) {
    	xil_printf("\n\r  ERROR %d: Memory not synchronized\n\r", res);
        this->IBFBSwitch.qdr_status = res;
	} else {
    	print("done.\n\r");
    }

    // init addresses for BP FPGA
    system_set_bp_addresses(this);
    // init interrupts
    this->Interrupt.init(&this->Interrupt);
    this->Interrupt.assign_handler(&this->Interrupt, XPAR_INTC_INST_UART_INST_INTERRUPT_INTR, &this->Shell, this->Shell.shell);
    this->Interrupt.assign_handler(&this->Interrupt, XPAR_INTC_INST_IBFB_FUNC_CTRL_CPU_INT_INTR, &this->IBFBSwitch.FunctionController, this->IBFBSwitch.FunctionController.interruptHandler);
    this->Interrupt.assign_handler(&this->Interrupt, XPAR_INTC_INST_IBFB_SWITCH_0_O_CPU_INT_INTR, &this->IBFBSwitch, this->IBFBSwitch.hw_int);
    this->Interrupt.assign_handler(&this->Interrupt, XPAR_INTC_INST_SYSTEM_SYS_5LVDS_4_P_0_INTR, &this->IBFBSwitch, this->IBFBSwitch.xfeltim_int);

	// register shell commands
    this->Shell.init(&this->Shell); //launch shell init function
	this->Shell.attach_cmd("help", &this->Shell, this->Shell.help);
	this->Shell.attach_cmd("version", &this->BPMService, this->BPMService.print_fw_version);
	this->Shell.attach_cmd("switch", &this->IBFBSwitch, this->IBFBSwitch.ibfb_cmd);

    this->BPMService.init_version_registers(&this->BPMService);

    // IBFB init
    this->IBFBSwitch.bpm_sel = this->BPMService.serviceRegs->cfg_bpm_sel;
    this->IBFBSwitch.init(&this->IBFBSwitch);

    print("done\n\n\r");
    this->Interrupt.enableInterrupts();
	this->Shell.prompt(&this->Shell);

	return;
}

int structSystem_new(struct structSystem *this) {

	/***********************************************************************************
	 * Build up the system of software component and make callbacks between them
	 ***********************************************************************************/
	//create BPM service object
	structBPMService_new(&this->BPMService, SYSTEM_SHARED_DDR2_SERVICE, XPAR_BPM_SERVICE_BASEADDR);

	// interrupt handler
	structInterrupt_new(&this->Interrupt, XPAR_INTC_INST_BASEADDR, this);

	// Create QDR2 object
	structQDR2_new(&this->QDR2, XPAR_QDR2_SPLB_BASEADDR);

	// create shell
	structShell_new(&this->Shell, STDIN_BASEADDRESS);

	// create IBFB switch
	structIBFBSwitch_new(
			&this->IBFBSwitch,
			XPAR_IBFB_SWITCH_0_BASEADDR,
			XPAR_QDR2_SPLB_MEM0_BASEADDR,
			IBFB_SWITCH_DDR2_BASE,
			XPAR_IBFB_FUNC_CTRL_BASEADDR,
			IBFB_FUNC_CTRL_MEM0_BASEADDR,
			IBFB_FUNC_CTRL_MEM_SIZE,
			XPAR_XFEL_TIM_SYS_RX_BASEADDR,
			XPAR_XFEL_TIM_SYS_RX_MEM0_BASEADDR);

	// system methods
	this->init_hardware = system_init_hardware;

	return 0;
}


