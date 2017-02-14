/*
 * gpac2_bpm_service_v1_00_a.c
 *
 *  Created on: 17.10.2013
 *      Author: koprek_w
 */


#include "bpm_service.h"

void service_set_init_error(struct structBPMService *this, unsigned int err) {

	unsigned int res = this->serviceRegs->errors;

	this->serviceRegs->errors = res | err | SERVICE_LED_1_RED_MASK | SERVICE_LED_2_RED_MASK;

	return;
}

void service_print_firmware_version(struct structBPMService *this){

	xil_printf("GPAC 2.1, BPM%d FPGA\n\r", this->serviceRegs->cfg_bpm_sel+1);
	xil_printf("\n\rFW ver: 0x%08X\n\r", this->serviceRegs->fw_version);
	xil_printf("FW com: %04d.%02d.%02d %02d:%02d\n\r",
			this->serviceRegs->fw_year,
			this->serviceRegs->fw_month,
			this->serviceRegs->fw_day,
			this->serviceRegs->fw_hour,
			this->serviceRegs->fw_minute);
	xil_printf("SW com: %04d.%02d.%02d %02d:%02d\n\r",
			DATE_YEAR, DATE_MONTH, DATE_DAY, TIME_HOUR, TIME_MINUTE);
	return;
}

void service_init_version_registers(struct structBPMService *this) {

	//strncpy((char *)(this->serviceRegs->sw_version), __DATE__, 11);
	//*(this->serviceRegs->sw_version+11) = ' ';
	//strncpy((char *)(this->serviceRegs->sw_version+12), __TIME__, 8);
	this->serviceRegs->sw_year = DATE_YEAR;
	this->serviceRegs->sw_month = DATE_MONTH;
	this->serviceRegs->sw_day = DATE_DAY;
	this->serviceRegs->sw_hour = TIME_HOUR;
	this->serviceRegs->sw_minute = TIME_MINUTE;
	this->mem->fw_version = this->serviceRegs->fw_version;
	this->mem->fw_year = this->serviceRegs->fw_year;
	this->mem->fw_month = this->serviceRegs->fw_month;
	this->mem->fw_day = this->serviceRegs->fw_day;
	this->mem->fw_hour = this->serviceRegs->fw_hour;
	this->mem->fw_minute = this->serviceRegs->fw_minute;
	this->mem->sw_year = this->serviceRegs->sw_year;
	this->mem->sw_month = this->serviceRegs->sw_month;
	this->mem->sw_day = this->serviceRegs->sw_day;
	this->mem->sw_hour = this->serviceRegs->sw_hour;
	this->mem->sw_minute = this->serviceRegs->sw_minute;


	return;
}


int structBPMService_new(struct structBPMService *this, unsigned int mem_addr, unsigned int base_addr) {

	this->mem = (struct structBPMServiceMem *)mem_addr;
	this->serviceRegs = (struct structBPMServiceRegs *)base_addr;
	this->print_fw_version = service_print_firmware_version;
	this->set_init_error = service_set_init_error;
	this->init_version_registers = service_init_version_registers;

	return 0;
}
