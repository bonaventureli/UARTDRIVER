//
//============================================================================
//
// Header file for the UART source code
//
//============================================================================
#ifndef _RLIN30_H
#define _RLIN30_H
#include "r_typedefs.h"

#define UART_BUFF_LEN 100

#define FRAME_HEAD  			0x7C  	// Frame Header
#define ADDR_CODE 			  0x01		// Address Code
	  	 
extern uint16_t gFrameLen;
extern uint8_t  gRecData[100];

//============================================================================
// Defines
//============================================================================
enum RLIN30_status
{
    RLIN30_busy,
    RLIN30_ready
};

//============================================================================
// Function defines
//============================================================================
void RLIN30_init(void);
void RLIN30_port_init(void);
void RLIN30_send_string(char send_string[] );
enum RLIN30_status RLIN30_get_status(void);
void RLIN30_table_setup(void);

void UartSent(uint8_t *Data,uint8_t Len);
void IntUart0Callback(uint32_t regEIIC_value);
void FrameCapture(uint8_t Data);

#endif
