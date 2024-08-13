#include "LPSPI.h"

//void LPSPI_Init(void) {
//	PCC->PCCn[PCC_LPSPI0_INDEX] |= ((1 << 30) | (6 << 24));
//    LPSPI1->CFGR1 = LPSPI_CFGR1_MASTER_MASK;
//    // [27] PCSCFG = 0, PCS[3:2] are enabled
//    // [26] OUTCFG = 0, Output data retains last value when CS negated
//    // [25-24] PINCFG = 0, SIN is input, SOUT is output
//    // [11-8] PCSPOL0 = 0b000, PCSn active low
//    // [0] MASTER = 1, Master mode

//    LPSPI1->TCR = 0x4308001F;
//    // [31] CPOL = 0, SCK inactive state is low
//    // [30] CPHA = 1, Change data on SCK leading edge
//    // [29-17] PRESCALE = 0, Functional clock divided by 1 = 24 MHz
//    // [25-24] PCS = 3, Transfer using PCS3
//    // [23] LSBF = 0, Data is transfered MSB first
//    // [22] BYSW = 0, Byte swap disabled
//    // [21] CONT = 0, Continuous transfer disabled
//    // [19] RXMSK = 1, Received data masked
//    // [18] TXMSK = 0, Normal transfer: data loaded from tx FIFO
//    // [16-17] WIDTH = 0, Single bit transfer
//    // [11-0] FRAMESZ = 32, # bits in frame = 31 + 1 = 32

//    LPSPI1->CCR = 0x0E0E0E2E;
//    // [31-24] SCKPCS = 15, SCK to PCS delay, (15 + 1) * (1 / 24 MHz)
//    // [23-16] PCSSCK = 15, PCS to SCK delay,  (15 + 1) * (1 / 24 MHz)
//    // [15-8] DBT = 15, Delay between Transfers, (15 + 1) * (1 / 24 MHz)
//    // [7-0] SCKDIV = 46, SCK divider, 24 MHz / (46 + 2) = 500kHz baud rate

//    LPSPI1->CR = 0x9;
//    // [3] DBGEN = 1, module enabled in debug mode
//    // [2] DOZEN = 0, module enabled in Doze mode
//    // [0] MEN = 1, Module is enabled
//}

//// 3. SPI Transmit and Receive functions
//uint8_t LPSPI1_transmit_8bits(uint8_t data) {
//    while (!(LPSPI0->SR & LPSPI_SR_TDF_MASK));  // Wait for Tx FIFO to have room
//    LPSPI0->TDR = data;
//    while (!(LPSPI0->SR & LPSPI_SR_RDF_MASK));  // Wait for Rx FIFO to have data
//    return LPSPI0->RDR;
//}
