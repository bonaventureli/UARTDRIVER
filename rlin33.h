//============================================================================
// PROJECT  :  F1L StarterKit
//============================================================================
//                           C O P Y R I G H T
//============================================================================
// Copyright (c) 2013 by Renesas Electronics  GmbH. All rights reserved.
// Arcadiastr.10
// D-40472 Duesseldorf
// Germany
//============================================================================
//
// Warranty Disclaimer :
// Because the Product(s) is licensed free of charge, there is no warranty of
// any kind whatsoever and expressly disclaimed and excluded by Renesas, either
// expressed or implied, including but not limited to those for non-
// infringement of intellectual property, merchantability and/or fitness for
// the particular purpose. Renesas shall not have any obligation to maintain,
// service or provide bug fixes for the supplied Product(s) and/or the
// Application.
//
// Each User is solely responsible for determining the appropriateness of
// using the Product(s) and assumes all risks associated with its exercise
// of rights under this Agreement, including, but not limited to the risks
// and costs of program errors, compliance with applicable laws, damage to
// or loss of data, programs or equipment, and unavailability or
// interruption of operations.
//
// Limitation of Liability :
// In no event shall Renesas be liable to the User for any incidental,
// consequential, indirect, or punitive damage (including but not limited to
// lost profits) regardless of whether such liability is based on breach of
// contract, tort, strict liability, breach of warranties, failure of
// essential purpose or otherwise and even if advised of the possibility of
// such damages. Renesas shall not be liable for any services or products provided
// by third party vendors, developers or consultants identified or referred
// to the User by Renesas in connection with the Product(s) and/or the
// Application.
//
//============================================================================
//
// Header file for the UART source code
//
//============================================================================
#ifndef _RLIN33_H
#define _RLIN33_H
#include "r_typedefs.h"

#define FRAME_HEAD  			0x7C  	// Frame Header
#define ADDR_CODE 			  0x01		// Address Code
#define UART3_BUFF_LEN 100

extern uint16_t gUart3FrameLen;
extern uint8_t gUart3RecData[UART3_BUFF_LEN];
//============================================================================
// Defines
//============================================================================
enum RLIN33_status
{
    RLIN33_busy,
    RLIN33_ready
};

//============================================================================
// Function defines
//============================================================================
void RLIN33_init(void);
void RLIN33_port_init(void);
void RLIN33_send_string(char send_string[] );
enum RLIN33_status RLIN33_get_status(void);
void RLIN33_table_setup(void);
void UartCallBack(uint8_t Res);
void Uart3Sent(uint8_t *Data,uint8_t Len);
void IntUart3Callback(uint32_t regEIIC_value);
void Uart3FrameCapture(uint8_t Data);

#endif
