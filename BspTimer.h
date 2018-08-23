#ifndef __BSP_TIMER_
#define __BSP_TIMER_

#include    "r_typedefs.h"
#include    "iodefine.h"

void    R_TAUD_Init( void );
void    R_TAUD_Start( void );
void 		SysTimeInc(void);
uint32_t GetTimeMs(void);
uint32_t GetTimeSec(void);
void TimerCallback(uint32_t regEIIC_value);

#endif