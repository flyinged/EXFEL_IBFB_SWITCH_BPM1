/*
 * shell.c
 *
 *  Created on: 22.11.2011
 *      Author: koprek_w
 */


#include "shell.h"

static struct structShellCmdDef {
    char cmd[SHELL_CMD_LEN];
    void *object;
    int (*do_action) (void *object, int argc, char *argv[]);
    char description[SHELL_CMD_DESC_LEN];
} mycmds[SHELL_NUM_OF_CMDS] = {
		{"help"   , NULL, NULL, "print this help"    },
		{"version", NULL, NULL, "print fw/sw version" },
		{"switch" , NULL, NULL, "IBFB switch test commands" },
};

int shell_find_cmd_index(char *cmd) {

	int i;

	for (i=0;i<SHELL_NUM_OF_CMDS;i++) {
		if (!strcmp(cmd, mycmds[i].cmd)) {
			return i;
		}
	}

	return -1;
}

void shell_attach_cmd(char *cmd, void *object, void *function) {

	int i = shell_find_cmd_index(cmd);

	if (i >= 0) {
		mycmds[i].do_action = function;
		mycmds[i].object = object;
	}

	return;
}

int shell_dummy(void *object, int argc, char *argv[]){

	return 0;
}

void shell_init(struct structShell *this){

	int i;

	for (i=0;i<SHELL_NUM_OF_CMDS;i++) {
		mycmds[i].do_action = shell_dummy;
		mycmds[i].object = this;
	}

	return;
}


int shell_help(void *object, int argc, char *argv[]){

	//struct structShell *this = (struct structShell *)object;
	int i;

	print("\n\rHelp list:\n\r");
	for (i=0;i<SHELL_NUM_OF_CMDS;i++)
		xil_printf("  %10s - %s\n\r", mycmds[i].cmd, mycmds[i].description);

	return 0;
}

void shell_prompt(struct structShell *this) {

	xil_printf("%s", SHELL_PROMPT);

	return;
}

void shell_parse_cmd(struct structShell *this) {

	int i;
	unsigned char argc = 0, word=0;
	char *argv[10];


	this->cmd[this->cmd_len] = '\0';

	if (!this->cmd_len) {
		shell_prompt(this);
		return;
	}
	//print("\n\n\r");
	//for (i=0;i<this->cmd_len;i++) {
	//	xil_printf("cmdlen: %d, 0x%02X ", this->cmd_len, this->cmd[i]);
	//}
	//print("\n\n\r");

	//separate command and argument with termination characters, link arguments to argv[]
	for (i=0;i<=this->cmd_len;i++) {
		if ((this->cmd[i] == SHELL_CHAR_SPACE) || (this->cmd[i] == SHELL_CHAR_NULL)) { // space
			if (word) //command/argument already parsed, go on
				argc++;
			this->cmd[i] = SHELL_CHAR_NULL; //terminate
			word = 0;
		}
		else { //valid character
			if (!word) { //beginning of an argument
				argv[argc] = &this->cmd[i];
			}
			word = 1;
		}
	}

	// find command
	if ( (i = shell_find_cmd_index(argv[0])) < 0) {
		xil_printf("\n\rCommand %s not found\n\r", argv[0]);
		i = 0;
	}
	//else { //if bad command, i = 0 => help is printed
		print("\n\r");
		mycmds[i].do_action(mycmds[i].object, argc, argv);
	//}

	this->cmd_len = 0;
	shell_prompt(this);

	return;
}


void shell_shell(struct structShell *this) {

	char c;
	unsigned int reg;

	reg = XUartLite_ReadReg(this->stdin_addr, XUL_STATUS_REG_OFFSET);
	if (!(reg & XUL_SR_RX_FIFO_VALID_DATA)) //only for RX FIFO not empty
		return;

	while (!XUartLite_IsReceiveEmpty(this->stdin_addr)) {
		c = XUartLite_ReadReg(this->stdin_addr, XUL_RX_FIFO_OFFSET);
		if (c >= SHELL_CHAR_SPACE) {
			xil_printf("%c", c);
			if (c == SHELL_CHAR_DEL) {
				if (this->cmd_len > 0)
					this->cmd_len--;
			}
			else
				this->cmd[this->cmd_len++] = c;
		}
		else {
			if ((c == '\r') || (c == '\n'))
				shell_parse_cmd(this); //parse and execute
		}
		if (this->cmd_len == SHELLL_BUFF_SIZE)
			this->cmd_len = 0;
	}

	return;
}




int structShell_new(struct structShell *this, unsigned int stdin_addr) {

	// properties
	this->stdin_addr = stdin_addr;
	memset(this->cmd, 0, SHELLL_BUFF_SIZE);
	this->cmd_len = 0;
	//this->shell_cmds = &mycmds;

	// methods
	this->init = shell_init;
	this->shell = shell_shell;
	this->prompt = shell_prompt;
	this->help = shell_help;
	this->attach_cmd = shell_attach_cmd;

	return 0;
}

