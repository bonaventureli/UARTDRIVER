/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :Mon, Oct 24, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "rlin30.h"
#include "rlin33.h"
#include "stdio.h"

extern void    R_CLOCK_Init( void );

void main(void);
char Str[]="RH850 \r\nUART3 Test\r\nWelcome to Here\r\n";

void main(void)
{
	R_CLOCK_Init();
	// set P10.3 output
	
	
	RLIN30_init();
	RLIN33_init();
	__EI();
	
	RLIN30_send_string("\r\nUART0 Test Enter the App");
	Uart3Sent((uint8_t*)Str,strlen(Str));
	while(1)
	{
	  __nop();
		
		if(gFrameLen )
		{
			sprintf(Str,"\r\nThe len of received Data is :%d",gFrameLen);
			RLIN30_send_string(Str);
			gFrameLen = 0;
		}
		if(gUart3FrameLen )
		{
			sprintf(Str,"\r\nThe len of received Data is :%d",gUart3FrameLen);
			Uart3Sent((uint8_t*)Str,strlen(Str));
			gUart3FrameLen = 0;
		}
	}

}
