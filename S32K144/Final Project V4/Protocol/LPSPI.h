/***********************************************************************
* File name: gpio.h
* Description: GPIO Configuration file of MCU module
* Version: 1.0
* Date:
*               8/7/2024: New
 ***********************************************************************/
#ifndef LPSPI_H
#define LPSPI_H

/***********************************************************************
 *         Inclusion
 ***********************************************************************/
#include "LPSPI_Register.h"

/***********************************************************************
 *         Function Prototype Denifition
 ***********************************************************************/
void LPSPI_Init(void);
uint8_t LPSPI1_transmit_8bits (uint8_t send);
//uint8_t LPSPI1_receive_8bits (void);
#endif
