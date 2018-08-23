//============================================================================
// Source code for the UART Functions
	
	/* Config RLIN33 Port Pins */ 
  /* RLIN33 TX on P1_1  */		// 1st Alternative 
  /* RLIN33 RX on P1_0  */
	/* OR */
	/* RLIN33 TX on P11_5 */   // 1st Alternative 
  /* RLIN33 RX on P11_6 */
//============================================================================

//============================================================================
// Includes
//============================================================================
//#include "device.h"
#include "rlin33.h"
#include "iodefine.h"
#include "r_typedefs.h"


/******************************************************************************
** Function:    UartClockSelect
** Description: Used for UART Clock Config
** Parameter:   None
** Return:      None
******************************************************************************/
void Uart3ClockSelect(void)
{
	uint32_t   reg32_value;

	/* Source Clock Setting for C_ISO_LIN
	CKSC_ILINS_CTL - C_ISO_LIN Source Clock Selection Register
	b31:b 2                    - Reserved set to 0
	b 1:b 0          ILINSCSID - Source Clock Setting for C_ISO_LIN  - CPUCLK2 */
	do
	{
	    reg32_value            = 0x00000001UL;
	    PROTCMD1               = 0x000000A5UL;   /* Protection release the CKSC_ILINS_CTL register   */
	    CKSC_ILINS_CTL         = reg32_value;
	    CKSC_ILINS_CTL         = ~reg32_value;
	    CKSC_ILINS_CTL         = reg32_value;
	} while ( PROTS1 != 0x00000000UL );
	while ( CKSC_ILINS_ACT != reg32_value )
	{
	    /* Wait for CKSC_ILINS_CTL to set. */
	}

	/* Clock Divider Setting for C_ISO_LIN
	CKSC_ILIND_CTL - C_ISO_LIN Divided Clock Selection Register
	b31:b 2                    - Reserved set to 0
	b 1:b 0          ILINDCSID - Source Clock Setting for C_ISO_LIN  - CKSC_ILINS_CTL selection / 1  */
	do
	{
	    reg32_value            = 0x00000001UL;
	    PROTCMD1               = 0x000000A5UL;   /* Protection release the CKSC_ILIND_CTL register   */
	    CKSC_ILIND_CTL         = reg32_value;
	    CKSC_ILIND_CTL         = ~reg32_value;
	    CKSC_ILIND_CTL         = reg32_value;
	} while ( PROTS1 != 0x00000000UL );
	while ( CKSC_ILIND_ACT != reg32_value );
}
/******************************************************************************
** Function:    RLIN33_init
** Description: Initialize the RLIN33 for UART 
** Parameter:   None
** Return:      None
******************************************************************************/
void RLIN33_init(void)
{
  /* RLIN33 is configured in UART mode with 115200 baud*/
  RLIN33_port_init();
  /* Disable RLIN */ 
  RLN33.LUOER=0x00;
  RLN33.LCUC=0x00;
  
	Uart3ClockSelect();
  
  /* IN Mode Register/UART Mode Register (LMD) */
  RLN33.LMD=0x01;      //UART mode
                      //LIN / UART System Clock: fa
                      //Module generates 1 interrupt signal
                      //3-bit majority voting logic for sampling RX data is enabled.
  
											/* LIN Wake-up Baud Rate Selector register  */
  RLN33.LWBR= 0xF0;//0x51;     //6 samples per bit 
	
  /* LIN Baud Rate Prescaler1/UART Baud Rate Prescaler */
  //RLN33.LBRP1=0x02;    //Baudrate = PCLK / (((BRP value) + 1)*(number of samples per bit)).
  //RLN33.LBRP0=0xb5;    //40MHZ/((21+1)*6)= 115200 baud
  RLN33.LBRP01.UINT16 = 21U; 

  /* LIN / UART Error Detection Enable Register */
  RLN33.LEDE=0x00;     //No error detection

  /* LIN Break Field Configuration Register/UART Configuration Register1 */
  RLN33.LBFC=0x00;     //UART 8-bit communication
                      //LSB first
                      //Stop Bit 1 bit
                      //Parity Disabled
                      //Without RX inversion
                      //Without RX inversion 

  /* LIN / UART Control Register */
  RLN33.LCUC=0x01;     //Set SW Reset request to inactive


  /* UART Operation Enable Register */ 
  RLN33.LUOER=0x03;    //UART Transmission Operation Enable Bit
                      //UART Reception Operation Enable Bit
      
	/* Set the interrupt flags */
  MKRLIN33UR0                = 1U;
  RFRLIN33UR0                = 0U;
  TBRLIN33UR0                = 0U;

  MKRLIN33UR1                = 1U;
  RFRLIN33UR1                = 0U;
  TBRLIN33UR1                = 0U;

  MKRLIN33UR2                = 1U;
  RFRLIN33UR2                = 0U;
  TBRLIN33UR2                = 0U; 
	
	/* Set the interrupt flags */
  MKRLIN33UR1                = 0U;                  /* Enable INTRLIN33UR1 interrupt     */
  MKRLIN33UR2                = 0U;                  /* Enable INTRLIN33UR2 interrupt     */
}

/******************************************************************************
** Function:    RLIN33_port_init
** Description: Configures P0_2 to alternative function RLIN33TX
**              Configures P0_3 to alternative function RLIN33RX
** Parameter:   None
** Return:      None
******************************************************************************/
void RLIN33_port_init(void)
{
    
  #if 0
	  /* RLIN33 TX on PIN 1 of Port 1 */
	  PMC1  |= 1 << 1;
	  PFC1  &= ~(1 << 1);
	  PM1   &= ~(1 << 1);  
	  /* RLIN33 RX on PIN 0 of Port 1 */
	  PMC1  |= 1 << 0;
	  PFC1  &=  ~(1 << 0);
	  PM1   |= 1 << 0;
	#else
		/* RLIN33 TX on PIN 5 of Port 11 */
	  PMC11  |= 1 << 5;
	  PFC11  &= ~(1 << 5);
	  PM11   &= ~(1 << 5);  
	  /* RLIN33 RX on PIN 6 of Port 11 */
	  PMC11  |= 1 << 6;
	  PFC11  &=  ~(1 << 6);
	  PM11   |= 1 << 6;
	#endif
}


/******************************************************************************
** Function:    RLIN33_send_string
** Description: Sends out a complete string via UART by using DirectMemoryAccess
** Parameter:   string to be send
** Return:      None
******************************************************************************/
void RLIN33_send_string( char send_string[] ) {

    unsigned short  us_string_length= 0x00;

    /* Calculate length of string send_string [] */
    while( send_string[ us_string_length ] != '\0' )
        ++us_string_length;
    
    /* Wait until transmission is finished */
    while((RLN33.LST&16)==16);
    
    /* Initialize DMA for sending bytes */
    while(DTS0DTE != 0);                     //Wait until last transmission is finished 
    
                                                    
    DTS0 = 0x00;                             //Disable DMA
    DTC0 = us_string_length-1;               //Number of times the DMA transfers(string length -1 because first trigger is manually given)
    DSA0 = (unsigned int)&send_string[1];    //Source Address = string buffer
    DDA0 = (unsigned int)&RLN33.LUTDR;        //Destination Address = RLIN transmit register
    DTCT0 = 0x0020;                          //8bit TransferSize / No Loop / Fixed Destination / Increment Source
    DTFR0 = 0x800a;                          //Trigger Enabled / Source = RLIN33 transmit interrupt
    DRQCLR = 1;                              //Clear DMA channel 0 request 
    DTS0 |= 0x01;                            //Enable DMA channel 0 transfer
    
    /* Start transmission */
    RLN33.LUTDR.UINT16 = send_string[0];             //Write first char to RLIN transmit register to start transmission
  
}

/******************************************************************************
** Function:    RLIN33_get_status
** Description: Returns if RLIN33 is busy or ready
** Parameter:   None
** Return:      RLIN33_busy
**              RLIN33_ready
******************************************************************************/
enum RLIN33_status RLIN33_get_status()
{
    if((RLN33.LST&16)==16)                   //If transmission bit is set
    {
        return RLIN33_busy;					//Return RLIN33 is busy
    }
    else									//If transmission bit is 0 (transmission ready)
    {
        return RLIN33_ready;                //Return RLIN33 is ready
    }
}


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
/*************************1*****************************************************
Private global variables and functions
******************************************************************************/
//static 
static uint16_t Res3;
/******************************************************************************
* Function Name : void IntUart3Callback(uint32_t regEIIC_value)
* Description   : This function is priority(7) interrupt processing. (direct vector)
* Argument      : regEIIC_value     : Interrupt factor
* Return Value  : none
******************************************************************************/
void IntUart3Callback(uint32_t regEIIC_value)
{
	if(0x000010DEUL == regEIIC_value )
  {
		Res3   =  RLN33.LURDR.UINT16;        // Echo
		Uart3FrameCapture(Res3);
  }
}

void Uart3SentOneByte(uint8_t Byte)
{
	RLN33.LUTDR.UINT16 = Byte;
	RFRLIN33UR0          = 0U;
	while ( !RFRLIN33UR0 ) {
                /* Wait for RFRLIN33UR0 to set. */
            }
  RFRLIN33UR0          = 0U;
}

void Uart3Sent(uint8_t *Data,uint8_t Len)
{
	uint8_t Temp;
	for(Temp=0; Temp<Len; Temp++)
	{
		Uart3SentOneByte(Data[Temp]);
	}
}

/******************************************************************************
** Function:    FrameCapture
** Description: Capture one frame from ISR
** Parameter:   Input data
** Return:      None
******************************************************************************/
uint16_t gUart3FrameLen;
uint8_t gUart3RecData[UART3_BUFF_LEN];
void Uart3FrameCapture(uint8_t Data)
{
	static uint16_t OffSet,DataLen;
	if(Data == 0x7C)
	{	
		DataLen = 0;
		gUart3RecData[0] = Data;
		OffSet = 1;
		
	}
	else
	{
		gUart3RecData[OffSet] = Data;
		OffSet++;
		if(OffSet == 5)
		{
			// Caclulate the len of valid data
			DataLen = ((0xFFFF&gUart3RecData[4])<<8)|gUart3RecData[3];
		}
		if(OffSet == DataLen+7)
		{
			gUart3FrameLen = OffSet;  // one frame was received
			//Check CRC-16
		}	
	}
	if(OffSet+1 > UART3_BUFF_LEN)
	{
		OffSet = 0; // overstep the boundary
	}	
}