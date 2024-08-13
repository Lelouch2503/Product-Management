/*******************************************************************************
* NXP Semiconductors
* (c) Copyright 2018 NXP Semiconductors
* ALL RIGHTS RESERVED.
********************************************************************************
Services performed by NXP in this matter are performed AS IS and without any
warranty. CUSTOMER retains the final decision relative to the total design
and functionality of the end product. NXP neither guarantees nor will be held
liable by CUSTOMER for the success of this project.
NXP DISCLAIMS ALL WARRANTIES, EXPRESSED, IMPLIED OR STATUTORY INCLUDING,
BUT NOT LIMITED TO, IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR
A PARTICULAR PURPOSE ON ANY HARDWARE, SOFTWARE ORE ADVISE SUPPLIED
TO THE PROJECT BY NXP, AND OR NAY PRODUCT RESULTING FROM NXP SERVICES.
IN NO EVENT SHALL NXP BE LIABLE FOR INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THIS AGREEMENT.
CUSTOMER agrees to hold NXP harmless against any and all claims demands
or actions by anyone on account of any damage, or injury, whether commercial,
contractual, or tortuous, rising directly or indirectly as a result
of the advise or assistance supplied CUSTOMER in connection with product,
services or goods supplied under this Agreement.
********************************************************************************
 * File:             main.c
 * Owner:            Daniel Martynek
 * Version:          3.0
 * Date:             Nov-12-2018
 * Classification:   General Business Information
 * Brief:            I2C master with MPL3115A2 sensor
********************************************************************************
Revision History:
3.0     Nov-12-2018     Daniel Martynek
*******************************************************************************/
#ifndef I2C_H_
#define I2C_H_
/*******************************************************************************
* Includes
*******************************************************************************/

#include "main.h"

typedef struct {
  volatile const  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
  volatile const  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
       uint8_t RESERVED_0[8];
  volatile uint32_t MCR;                               /**< Master Control Register, offset: 0x10 */
  volatile uint32_t MSR;                               /**< Master Status Register, offset: 0x14 */
  volatile uint32_t MIER;                              /**< Master Interrupt Enable Register, offset: 0x18 */
  volatile uint32_t MDER;                              /**< Master DMA Enable Register, offset: 0x1C */
  volatile uint32_t MCFGR0;                            /**< Master Configuration Register 0, offset: 0x20 */
  volatile uint32_t MCFGR1;                            /**< Master Configuration Register 1, offset: 0x24 */
  volatile uint32_t MCFGR2;                            /**< Master Configuration Register 2, offset: 0x28 */
  volatile uint32_t MCFGR3;                            /**< Master Configuration Register 3, offset: 0x2C */
       uint8_t RESERVED_1[16];
  volatile uint32_t MDMR;                              /**< Master Data Match Register, offset: 0x40 */
       uint8_t RESERVED_2[4];
  volatile uint32_t MCCR0;                             /**< Master Clock Configuration Register 0, offset: 0x48 */
       uint8_t RESERVED_3[4];
  volatile uint32_t MCCR1;                             /**< Master Clock Configuration Register 1, offset: 0x50 */
       uint8_t RESERVED_4[4];
  volatile uint32_t MFCR;                              /**< Master FIFO Control Register, offset: 0x58 */
  volatile const  uint32_t MFSR;                              /**< Master FIFO Status Register, offset: 0x5C */
  volatile  uint32_t MTDR;                              /**< Master Transmit Data Register, offset: 0x60 */
       uint8_t RESERVED_5[12];
  volatile const  uint32_t MRDR;                              /**< Master Receive Data Register, offset: 0x70 */
       uint8_t RESERVED_6[156];
  volatile uint32_t SCR;                               /**< Slave Control Register, offset: 0x110 */
  volatile uint32_t SSR;                               /**< Slave Status Register, offset: 0x114 */
  volatile uint32_t SIER;                              /**< Slave Interrupt Enable Register, offset: 0x118 */
  volatile uint32_t SDER;                              /**< Slave DMA Enable Register, offset: 0x11C */
       uint8_t RESERVED_7[4];
  volatile uint32_t SCFGR1;                            /**< Slave Configuration Register 1, offset: 0x124 */
  volatile uint32_t SCFGR2;                            /**< Slave Configuration Register 2, offset: 0x128 */
       uint8_t RESERVED_8[20];
  volatile uint32_t SAMR;                              /**< Slave Address Match Register, offset: 0x140 */
       uint8_t RESERVED_9[12];
  volatile const  uint32_t SASR;                              /**< Slave Address Status Register, offset: 0x150 */
  volatile uint32_t STAR;                              /**< Slave Transmit ACK Register, offset: 0x154 */
       uint8_t RESERVED_10[8];
  volatile  uint32_t STDR;                              /**< Slave Transmit Data Register, offset: 0x160 */
       uint8_t RESERVED_11[12];
  volatile const  uint32_t SRDR;                              /**< Slave Receive Data Register, offset: 0x170 */
} LPI2C_Type, *LPI2C_MemMapPtr;

 /** Number of instances of the LPI2C module. */
#define LPI2C_INSTANCE_COUNT                     (1u)


/* LPI2C - Peripheral instance base addresses */
/** Peripheral LPI2C0 base address */
#define LPI2C0_BASE                              (0x40066000u)
/** Peripheral LPI2C0 base pointer */
#define LPI2C0                                   ((LPI2C_Type *)LPI2C0_BASE)

#define PCC_LPI2C0 															 (*(volatile unsigned int*)(0x40065000 + 0x198))

/*******************************************************************************
* Constants and macros
*******************************************************************************/
enum err
{
    OK,
    BUSY,
    NO_DATA_RECEIVED,
    NO_STOP,
    NDF,
    ALF,
    FEF,
    PLTF
};

#define BUSY_TIMEOUT        1000
#define READING_TIMEOUT     2000
#define STOP_TIMEOUT        3000

/*******************************************************************************
* Function prototypes
*******************************************************************************/
uint8_t LPI2C0_read(uint8_t address, uint8_t reg, uint8_t *p_buffer, uint8_t n_bytes);
uint8_t LPI2C0_writeMulti(uint8_t s_w_address, uint8_t s_reg_address, uint8_t *byte, uint8_t n_bytes);
uint8_t LPI2C0_write(uint8_t s_w_address, uint8_t s_reg_address, uint8_t byte);
void LPI2C0_Master_IRQHandler(void);
void LPI2C0_init(void);
void LPI2C0_clock(void);
void LPI2C0_IRQs(void);

#endif /* I2C_H_ */
