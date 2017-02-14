/*
 * shell.h
 *
 *  Created on: 22.11.2011
 *      Author: koprek_w
 */

#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <string.h>
#include "xuartlite_l.h"

#define SHELLL_BUFF_SIZE	256
#define SHELL_PROMPT		"\r\n$>"
#define SHELL_CHAR_NULL			0x00
#define SHELL_CHAR_SPACE		0x20
#define SHELL_CHAR_DEL			0x7F

#define SHELL_NUM_OF_CMDS		3
#define SHELL_CMD_LEN			20
#define SHELL_CMD_DESC_LEN		50



struct structShell{
	unsigned int stdin_addr;
	char cmd[SHELLL_BUFF_SIZE];
	unsigned short cmd_len;
	void (*init)(struct structShell *);
	void (*shell)(struct structShell *);
	void (*prompt)(struct structShell *);
	int (*help)(void *object, int argc, char *argv[]);
	void (*attach_cmd)(char *cmd, void *object, void *function);
};


int structShell_new(struct structShell *this, unsigned int stdin_addr);


#endif /* SHELL_H_ */
