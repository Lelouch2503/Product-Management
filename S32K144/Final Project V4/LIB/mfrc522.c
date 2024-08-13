#include "mfrc522.h"

void 	TM_SPI_Init(void) {        
	/*(default) Peripheral is present.	
	 * Enable PCS=SPLL_DIV2 (40 MHz func'l clock) */
	PCC->PCCn[PCC_LPSPI0_INDEX] |= 	(ENABLE_PCC	
								 |PCC_PCCn_PCS(6));
	/*LPSPI0 Initialization
	 * Disable module for configuration
	 * Interrupts not used
	 * DMA not used  
	 * Defaults: 
	 * RDM0=0: rec'd data to FIFO as normal
	 * CIRFIFO=0; Circular FIFO is disabled
	 * HRSEL, HRPOL, HREN=0: Host request disabled
	 * */
	LPSPI0->CR    = 0x00000000;
	LPSPI0->IER   = 0x00000000;
	LPSPI0->DER   = 0x00000000;
	LPSPI0->CFGR0 = 0x00000000;
	/* Configurations: master mode
	 * PCSCFG=0: PCS[3:2] are enabled
	 * OUTCFG=0: Output data retains last value when CS negated
	 * PINCFG=0: SIN is input, SOUT is output  
	 * MATCFG=0: Match disabled
	 * PCSPOL=0: PCS is active low
	 * NOSTALL=0: Stall if Tx FIFO empty or Rx FIFO full
	 * AUTOPCS=0: does not apply for master mode
	 * SAMPLE=0: input data sampled on SCK edge 
	 * MASTER=1: Master mode*/
	LPSPI0->CFGR1 = LPSPI_CFGR1_MASTER_MASK;  
	/* Transmit cmd: PCS3, 16 bits, prescale func'l clk by 4, etc
	 * CPOL=0: SCK inactive state is low 
	 * CPHA=1: Change data on SCK lead'g, capture on trail'g edge
	 * PRESCALE=2: Functional clock divided by 2**2 = 4
	 * PCS=3: Transfer using PCS3
	 * LSBF=0: Data is transfered MSB first
	 * BYSW=0: Byte swap disabled
	 * CONT, CONTC=0: Continuous transfer disabled
	 * RXMSK=0: Normal transfer: rx data stored in rx FIFO
	 * TXMSK=0: Normal transfer: data loaded from tx FIFO
	 * WIDTH=0: Single bit transfer
	 * FRAMESZ=15: # bits in frame = 15+1=16 */
	LPSPI0->TCR   = LPSPI_TCR_PRESCALE(2)
									|LPSPI_TCR_PCS(0)
									|LPSPI_TCR_FRAMESZ(7);
	/* Clock dividers based on prescaled func'l clk of 100 nsec
	 * SCKPCS=4: SCK to PCS delay = 4+1 = 5 (500 nsec)
	 * PCSSCK=4: PCS to SCK delay = 9+1 = 10 (1 usec) 
	 * DBT=8: Delay between Transfers = 8+2 = 10 (1 usec) 
	 * SCKDIV=8: SCK divider =8+2 = 10 (1 usec: 1 MHz baud rate) */
	LPSPI0->CCR   = LPSPI_CCR_SCKPCS(4)
				  |LPSPI_CCR_PCSSCK(4)
				  |LPSPI_CCR_DBT(8)
				  |LPSPI_CCR_SCKDIV(4); 
	/* RXWATER=0: Rx flags set when Rx FIFO >0
	 * TXWATER=3: Tx flags set when Tx FIFO <= 3  */

  LPSPI0->FCR   = LPSPI_FCR_RXWATER(0)   	/* RXWATER=0: Rx flags set when Rx FIFO >0 	*/
                 |	LPSPI_FCR_TXWATER(1);	/* TXWATER=3: Tx flags set when Tx FIFO <= 3 	*/
	/* Enable module for operation
	 * DBGEN=1: module enabled in debug mode 
	 * DOZEN=0: module enabled in Doze mode
	 * RST=0: Master logic not reset
	 * MEN=1: Module is enabled  */
	LPSPI0->CR    = LPSPI_CR_MEN_MASK
				  |LPSPI_CR_DBGEN_MASK;
}

uint8_t TM_SPI_Send(uint8_t data)
{
	uint8_t ret;
	while((LPSPI0->SR & LPSPI_SR_TDF_MASK)>>LPSPI_SR_TDF_SHIFT==0);
	/* Wait for Tx FIFO available */

	LPSPI0->TDR = LPSPI_TDR_DATA(data); /* Transmit data */
	while((LPSPI0->SR & LPSPI_SR_TCF_MASK)>>LPSPI_SR_TCF_SHIFT==0) {}
	LPSPI0->SR |= LPSPI_SR_TCF_MASK;

	while((LPSPI0->SR & (1 << 24)))	 {}
		
	while((LPSPI0->SR & LPSPI_SR_RDF_MASK)>>LPSPI_SR_RDF_SHIFT==0){}
		
	//CHANGE " " -> (uint8_t)
	ret = (uint8_t)LPSPI0->RDR;
	LPSPI0->SR = LPSPI_SR_RDF_MASK; /* Clear RDF flag */

	return ret;
}

void TM_MFRC522_Init(void) {


	TM_MFRC522_Reset();

	TM_MFRC522_WriteRegister(MFRC522_REG_T_MODE, 0x8D);
	TM_MFRC522_WriteRegister(MFRC522_REG_T_PRESCALER, 0x3E);
	TM_MFRC522_WriteRegister(MFRC522_REG_T_RELOAD_L, 30);           
	TM_MFRC522_WriteRegister(MFRC522_REG_T_RELOAD_H, 0);

	/* 48dB gain */
	TM_MFRC522_WriteRegister(MFRC522_REG_RF_CFG, 0x70); //111: 48 dB
	
	TM_MFRC522_WriteRegister(MFRC522_REG_TX_AUTO, 0x40); 
	/*100: 1: reserved, 00:3-state; in soft power-down the drivers are only in 3-state
		mode if the DriverSel[1:0] value is set to 3-state mode*/
	
	TM_MFRC522_WriteRegister(MFRC522_REG_MODE, 0x3D); //
	//0011 1101
	// [3] = 1: 1 polarity of pin MFIN is active HIGH
	// [5] = 1:  transmitter can only be started if an RF field is generated

	TM_MFRC522_AntennaOn();		//Open the antenna
}

TM_MFRC522_Status_t TM_MFRC522_Check(uint8_t* id) {
	TM_MFRC522_Status_t status;
	//Find cards, return card type
	status = TM_MFRC522_Request(PICC_REQIDL, id);	
	if (status == MI_OK) {
		//Card detected
		//Anti-collision, return card serial number 4 bytes
		status = TM_MFRC522_Anticoll(id);	
	}
	TM_MFRC522_Halt();			//Command card into hibernation 

	return status;
}

TM_MFRC522_Status_t TM_MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID) {
	uint8_t i;
	for (i = 0; i < 5; i++) {
		if (CardID[i] != CompareID[i]) {
			return MI_ERR;
		}
	}
	return MI_OK;
}

//==================================================
//ham nay can thay doi vi cau truc F1 khac F4

void TM_MFRC522_WriteRegister(uint8_t addr, uint8_t val) {
	//CS low
	MFRC522_CS_LOW;
	//Send address
	TM_SPI_Send((addr << 1) & 0x7E);
	//Send data	
	TM_SPI_Send(val);
	//CS high
	MFRC522_CS_HIGH;
}

uint8_t TM_MFRC522_ReadRegister(uint8_t addr) {
	uint8_t val;
	//CS low

	MFRC522_CS_LOW;
	TM_SPI_Send(((addr << 1) & 0x7E) | 0x80);	
	val = TM_SPI_Send(MFRC522_DUMMY);
	//CS high
	MFRC522_CS_HIGH;
	return val;	
}

void TM_MFRC522_SetBitMask(uint8_t reg, uint8_t mask) {
	TM_MFRC522_WriteRegister(reg, TM_MFRC522_ReadRegister(reg) | mask);
}

void TM_MFRC522_ClearBitMask(uint8_t reg, uint8_t mask){
	TM_MFRC522_WriteRegister(reg, TM_MFRC522_ReadRegister(reg) & (~mask));
} 

void TM_MFRC522_AntennaOn(void) {
	uint8_t temp;

	temp = TM_MFRC522_ReadRegister(MFRC522_REG_TX_CONTROL);
	// TxControlReg [1:0]
	// 1: output signal on pin TX2 delivers the 13.56 MHz energy carrier
  // modulated by the transmission data
	// 0: output signal on pin TX1 delivers the 13.56 MHz energy carrier
	// modulated by the transmission data
	
	// Check the first 2 bit of TxControlReg, if 2 bit is not set, set it
	if (!(temp & 0x03)) {
		TM_MFRC522_SetBitMask(MFRC522_REG_TX_CONTROL, 0x03);
	}
}

void TM_MFRC522_AntennaOff(void) {
	
	// Clear first 2 bit of TxControlReg to turn antennaoff
	TM_MFRC522_ClearBitMask(MFRC522_REG_TX_CONTROL, 0x03);
}

void TM_MFRC522_Reset(void) {
	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_RESETPHASE);
}

TM_MFRC522_Status_t TM_MFRC522_Request(uint8_t reqMode, uint8_t* TagType) {
	TM_MFRC522_Status_t status;  
	uint16_t backBits;			//The received data bits

	TM_MFRC522_WriteRegister(MFRC522_REG_BIT_FRAMING, 0x07);		//TxLastBists = BitFramingReg[2..0]	???

	TagType[0] = reqMode;
	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

	if ((status != MI_OK) || (backBits != 0x10)) {    
		status = MI_ERR;
	}

	return status;
}

TM_MFRC522_Status_t TM_MFRC522_ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen) {
	TM_MFRC522_Status_t status = MI_ERR;
	uint8_t irqEn = 0x00;
	uint8_t waitIRq = 0x00;
	uint8_t lastBits;
	uint8_t n;
	uint16_t i;

	switch (command) {
		case PCD_AUTHENT: {
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE: {
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
			break;
	}

	TM_MFRC522_WriteRegister(MFRC522_REG_COMM_IE_N, irqEn | 0x80);
	TM_MFRC522_ClearBitMask(MFRC522_REG_COMM_IRQ, 0x80);
	TM_MFRC522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80); // clears the internal FIFO buffer’s read and write pointer
																											 // and ErrorReg register’s BufferOvfl bit
																											 // reading this bit always returns 0

	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_IDLE); // no action, cancels current command execution

	//Writing data to the FIFO
	for (i = 0; i < sendLen; i++) {   
		TM_MFRC522_WriteRegister(MFRC522_REG_FIFO_DATA, sendData[i]);    
	}

	//Execute the command
	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, command);
	if (command == PCD_TRANSCEIVE) {    
		TM_MFRC522_SetBitMask(MFRC522_REG_BIT_FRAMING, 0x80);		//StartSend=1,transmission of data starts  
	}   

	//Waiting to receive data to complete
	i = 2000;	//i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms???
	do {
		//CommIrqReg[7..0]
		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
		n = TM_MFRC522_ReadRegister(MFRC522_REG_COMM_IRQ);
		i--;
	} while ((i!=0) && !(n&0x01) && !(n&waitIRq));

	TM_MFRC522_ClearBitMask(MFRC522_REG_BIT_FRAMING, 0x80);			//StartSend=0

	if (i != 0)  {
		if (!(TM_MFRC522_ReadRegister(MFRC522_REG_ERROR) & 0x1B)) {
			status = MI_OK;
			if (n & irqEn & 0x01) {   
				status = MI_NOTAGERR;			
			}

			if (command == PCD_TRANSCEIVE) {
				n = TM_MFRC522_ReadRegister(MFRC522_REG_FIFO_LEVEL);
				lastBits = TM_MFRC522_ReadRegister(MFRC522_REG_CONTROL) & 0x07;
				//				2 to 0 RxLastBits[2:0] - indicates the number of valid bits in the last received byte
				//        this value is 000b, the whole byte is valid
				if (lastBits) {   
					*backLen = (n - 1) * 8 + lastBits;   
				} else {   
					*backLen = n * 8;   
				}

				if (n == 0) {   
					n = 1;    
				}
				if (n > MFRC522_MAX_LEN) {   
					n = MFRC522_MAX_LEN;   
				}

				//Reading the received data in FIFO
				for (i = 0; i < n; i++) {   
					backData[i] = TM_MFRC522_ReadRegister(MFRC522_REG_FIFO_DATA);    
				}
			}
		} else {   
			status = MI_ERR;  
		}
	}

	return status;
}

TM_MFRC522_Status_t TM_MFRC522_Anticoll(uint8_t* serNum) {
	TM_MFRC522_Status_t status;
	uint8_t i;
	uint8_t serNumCheck = 0;
	uint16_t unLen;

	TM_MFRC522_WriteRegister(MFRC522_REG_BIT_FRAMING, 0x00);		//TxLastBists = BitFramingReg[2..0]
	
//	2 to 0 TxLastBits[2:0] - used for transmission of bit oriented frames: defines the 
//  number of bits of the last byte that will be transmitted
//  000b indicates that all bits of the last byte will be transmitted

	serNum[0] = PICC_ANTICOLL; // Chong doi khi dung nhieu the
	serNum[1] = 0x20;
	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

	if (status == MI_OK) {
		//Check card serial number
		for (i = 0; i < 4; i++) {   
			serNumCheck ^= serNum[i];
		}
		if (serNumCheck != serNum[i]) {   
			status = MI_ERR;    
		}
	}
	return status;
} 

void TM_MFRC522_CalculateCRC(uint8_t*  pIndata, uint8_t len, uint8_t* pOutData) {
	uint8_t i, n;

	TM_MFRC522_ClearBitMask(MFRC522_REG_DIV_IRQ, 0x04);			//CRCIrq = 0
	TM_MFRC522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);			//Clear the FIFO pointer
	//Write_MFRC522(CommandReg, PCD_IDLE);

	//Writing data to the FIFO	
	for (i = 0; i < len; i++) {   
		TM_MFRC522_WriteRegister(MFRC522_REG_FIFO_DATA, *(pIndata+i));   
	}
	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_CALCCRC);

	//Wait CRC calculation is complete
	i = 0xFF;
	do {
		n = TM_MFRC522_ReadRegister(MFRC522_REG_DIV_IRQ);
		i--;
		} while ((i!=0) && !(n&0x04));			//CRCIrq = 1:  the CalcCRC command is active and all data is processed


	//Read CRC calculation result
	pOutData[0] = TM_MFRC522_ReadRegister(MFRC522_REG_CRC_RESULT_L);
	pOutData[1] = TM_MFRC522_ReadRegister(MFRC522_REG_CRC_RESULT_M);
}

uint8_t TM_MFRC522_SelectTag(uint8_t* serNum) {
	uint8_t i;
	TM_MFRC522_Status_t status;
	uint8_t size;
	uint16_t recvBits;
	uint8_t buffer[9]; 

	buffer[0] = PICC_SElECTTAG;
	buffer[1] = 0x70;
	for (i = 0; i < 5; i++) {
		buffer[i+2] = *(serNum+i);
	}
	TM_MFRC522_CalculateCRC(buffer, 7, &buffer[7]);		//??
	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);

	if ((status == MI_OK) && (recvBits == 0x18)) {   
		size = buffer[0]; 
	} else {   
		size = 0;    
	}

	return size;
}

TM_MFRC522_Status_t TM_MFRC522_Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t* Sectorkey, uint8_t* serNum) {
	TM_MFRC522_Status_t status;
	uint16_t recvBits;
	uint8_t i;
	uint8_t buff[12]; 

	//Verify the command block address + sector + password + card serial number
	buff[0] = authMode;
	buff[1] = BlockAddr;
	for (i = 0; i < 6; i++) {    
		buff[i+2] = *(Sectorkey+i);   
	}
	for (i=0; i<4; i++) {    
		buff[i+8] = *(serNum+i);   
	}
	status = TM_MFRC522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);

	if ((status != MI_OK) || (!(TM_MFRC522_ReadRegister(MFRC522_REG_STATUS2) & 0x08))) {   
		status = MI_ERR;   
	}

	return status;
}

TM_MFRC522_Status_t TM_MFRC522_Read(uint8_t blockAddr, uint8_t* recvData) {
	TM_MFRC522_Status_t status;
	uint16_t unLen;

	recvData[0] = PICC_READ;
	recvData[1] = blockAddr;
	TM_MFRC522_CalculateCRC(recvData,2, &recvData[2]);
	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

	if ((status != MI_OK) || (unLen != 0x90)) {
		status = MI_ERR;
	}

	return status;
}

TM_MFRC522_Status_t TM_MFRC522_Write(uint8_t blockAddr, uint8_t* writeData) {
	TM_MFRC522_Status_t status;
	uint16_t recvBits;
	uint8_t i;
	uint8_t buff[18]; 

	buff[0] = PICC_WRITE;
	buff[1] = blockAddr;
	TM_MFRC522_CalculateCRC(buff, 2, &buff[2]);
	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

	if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) {   
		status = MI_ERR;   
	}

	if (status == MI_OK) {
		//Data to the FIFO write 16Byte
		for (i = 0; i < 16; i++) {    
			buff[i] = *(writeData+i);   
		}
		TM_MFRC522_CalculateCRC(buff, 16, &buff[16]);
		status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);

		if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) {   
			status = MI_ERR;   
		}
	}

	return status;
}

void TM_MFRC522_Halt(void) {
	uint16_t unLen;
	uint8_t buff[4]; 

	buff[0] = PICC_HALT;
	buff[1] = 0;
	TM_MFRC522_CalculateCRC(buff, 2, &buff[2]);

	TM_MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &unLen);
}
