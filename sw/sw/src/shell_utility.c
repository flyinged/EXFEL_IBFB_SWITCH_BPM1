/*
 * shell_utility.c
 *
 *  Created on: 15.01.2016
 *      Author: malatesta_a
 */

/*
 * uart_utility.c
 *
 *  Created on: 02.10.2015
 *      Author: malatesta_a
 */


#include "shell_utility.h"

/* declaration of extern functions */
extern void outbyte (char);
extern char inbyte (void);


unsigned long hex_from_console(char* msg, unsigned char max){

    char inchar[9];
    unsigned long step, i;
    unsigned long outval;

    print(msg);
    //13=CR
    //48='0'

    //first get string
    step = 0;
    while(1) {
    	inchar[step] = inbyte(); //get char into buffer
    	outbyte(inchar[step]);

        if (inchar[step] == 13 ) { //check if termination character
            break;
        } else if (
                inchar[step]<48 ||
                (inchar[step]>57 && inchar[step]<65) ||
                (inchar[step]>70 && inchar[step]<97) ||
                inchar[step]>102 ) { //check if character is valid
            step = 0;
            print("\r\nNot a valid hex digit\r\n");
        } else if (step == 8) { //check if string is too long
            step = 0;
            print("\r\nHex number is too big: maximum 32 bits allowed.\r\n");
        } else { //continue
            inchar[step+1] = 0;
            step++;
        }

        if (step==max) break;
    }

    print("\n\r");

    //now process the value
    outval = 0;
    for (i = 0; i < step; i++) {
        switch (inchar[i]) {
        case 48 ... 57:
            outval += ( (inchar[i]-48) << ((step-i-1)*4) );
            break;
        case 65 ... 70:
            outval += ( (inchar[i]-55) << ((step-i-1)*4) );
            break;
        case 97 ... 102:
            outval += ( (inchar[i]-87) << ((step-i-1)*4) );
            break;
        }
    }

    return outval;
}


//uint8_t str_from_console(uint8_t* msg, uint8_t *str){
//
//    uint8_t i, rx_size;
//    uint32_t tic;
//
//    tic = tick_counter;
//
//    MSS_UART_polled_tx_string( &g_mss_uart0, (const uint8_t *) msg);
//    //13=CR
//    //48='0'
//
//    //get string
//    i = 0;
//    while(1){
//        do {
//            MSS_WD_reload();
//            rx_size = MSS_UART_get_rx ( &g_mss_uart0, str+i, 1 );
//            if ((tick_counter-tic) > TOUT) { //1 minute timeout
//                MSS_UART_polled_tx_string( &g_mss_uart0, (const uint8_t *) "\n\rTIMEOUT while waiting for user input\n\r");
//                return 0;
//            }
//        } while (rx_size == 0);
//
//        if (str[i] == 13) { //check if termination character
//            MSS_UART_polled_tx( &g_mss_uart0, (uint8_t*)"\n\r", 2);
//            break;
//        } else {
//            MSS_UART_polled_tx( &g_mss_uart0, str+i, 1);
//            i++;
//        }
//    }
//    str[i] = '\0';
//
//    return(i);
//}

