#ifndef _LPUARTH_H_
#define _LPUARTH_H_

#include "LPUART_Register.h"

void LPUART_init(LPUART_Type *base,  uint32_t baud_rate, Clock_Source clk_src) ;
void LPUARTx_SendByte(LPUART_Type *base, uint8_t data);
void LPUARTx_SendString(LPUART_Type *LPUARTx, char *data);
uint8_t LPUARTx_ReadByte(LPUART_Type *base);
uint32_t get_clock_frequency(Clock_Source clk_src);


/* LPUART interrupt*/
void LPUART0_RxTx_IRQHandler(void);
#endif
