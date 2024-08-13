#ifndef FLASH_H
#define FLASH_H

/***********************************************************************
 *         				Inclusion
 ***********************************************************************/
#include "flash_register.h"

/***********************************************************************
						Function Prototype 
 ***********************************************************************/
void EraseFlash(uint32_t address);
uint8_t WriteFlash(uint32_t address, uint8_t *data, uint32_t length);
void ReadFlash(uint32_t address, uint8_t *data, uint32_t length);

#endif
