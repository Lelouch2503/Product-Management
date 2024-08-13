#include "flash.h"
void EraseFlash(uint32_t address) {
	
	uint32_t alignedAddress;
	
		// Ensure the address is aligned to an 8-byte boundary
	alignedAddress = address & ~(0x7u);
	//erase 4KB flash sector (the smallest entity that can be erased) at 0x0004_0000
	while((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0);	//wait if operation in progress
	FTFC->FSTAT = FTFC_FSTAT_ACCERR_MASK | FTFC_FSTAT_FPVIOL_MASK;	//clear flags if set

	FTFC->FCCOB[3] = 0x09;	//Erase Flash Sector command (0x09)
	FTFC->FCCOB[2] = (alignedAddress >> 16) & 0xFF;  // Address [23:16]
	FTFC->FCCOB[1] = (alignedAddress >> 8) & 0xFF;   // Address [15:8]
	FTFC->FCCOB[0] = alignedAddress & 0xFF;          // Address [7:0]

	FTFC->FSTAT = FTFC_FSTAT_CCIF_MASK;	//launch command
	while((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0);	//wait for done
}

uint8_t WriteFlash(uint32_t address, uint8_t *data, uint32_t length) {
	uint32_t alignedAddress;
	uint32_t i;

	// Ensure the address is aligned to an 8-byte boundary
	alignedAddress = address & ~(0x7u);

	for (i = 0; i < length; i += 8) {
			// Wait for any ongoing flash operations to complete
			while ((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0);

			// Clear any existing errors
			FTFC->FSTAT = FTFC_FSTAT_FPVIOL_MASK | FTFC_FSTAT_ACCERR_MASK | FTFC_FSTAT_RDCOLERR_MASK;

			// Set up the flash command
			FTFC->FCCOB[3] = 0x07;  // Program Phrase command
			FTFC->FCCOB[2] = (alignedAddress >> 16) & 0xFF;  // Address [23:16]
			FTFC->FCCOB[1] = (alignedAddress >> 8) & 0xFF;   // Address [15:8]
			FTFC->FCCOB[0] = alignedAddress & 0xFF;          // Address [7:0]

			// Load data into FCCOB registers
			for (uint16_t j = 0; j < 8 && (i + j) < length; j++) {
					FTFC->FCCOB[4 + j] = data[i + j];
			}

			// Launch the command
			FTFC->FSTAT = FTFC_FSTAT_CCIF_MASK;

			// Wait for the command to complete
			while ((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0);

			// Check for errors
			if (FTFC->FSTAT & (FTFC_FSTAT_MGSTAT0_MASK | FTFC_FSTAT_FPVIOL_MASK | FTFC_FSTAT_ACCERR_MASK)) {
					return FLASH_ERROR_PROGRAM;
			}

			alignedAddress += 8;
	}

   return FLASH_OK;
}

void ReadFlash(uint32_t address, uint8_t *data, uint32_t length) {
	uint8_t i;
	uint8_t *flash_ptr = (uint8_t *)address;

	for (i = 0; i < length; i++) {
			data[i] = flash_ptr[i];
	}
}
