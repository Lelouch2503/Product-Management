#ifndef FLASH_REG_H
#define FLASH_REG_H

#include "main.h"

/*******************************************************************************
Typedef Denifition
 *******************************************************************************/

typedef struct {
  volatile uint8_t FSTAT;                              /**< Flash Status Register, offset: 0x0 */
  volatile uint8_t FCNFG;                              /**< Flash Configuration Register, offset: 0x1 */
  volatile const  uint8_t FSEC;                               /**< Flash Security Register, offset: 0x2 */
  volatile const  uint8_t FOPT;                               /**< Flash Option Register, offset: 0x3 */
  volatile uint8_t FCCOB[12u];            /**< Flash Common Command Object Registers, array offset: 0x4, array step: 0x1 */
  volatile uint8_t FPROT[4u];            /**< Program Flash Protection Registers, array offset: 0x10, array step: 0x1 */
       uint8_t RESERVED_0[2];
  volatile uint8_t FEPROT;                             /**< EEPROM Protection Register, offset: 0x16 */
  volatile uint8_t FDPROT;                             /**< Data Flash Protection Register, offset: 0x17 */
       uint8_t RESERVED_1[20];
  volatile const  uint8_t FCSESTAT;                           /**< Flash CSEc Status Register, offset: 0x2C */
       uint8_t RESERVED_2[1];
  volatile uint8_t FERSTAT;                            /**< Flash Error Status Register, offset: 0x2E */
  volatile uint8_t FERCNFG;                            /**< Flash Error Configuration Register, offset: 0x2F */
} FTFC_Type;

/***********************************************************************
 *         Macro Denifition
 ***********************************************************************/

/** Peripheral FTFC base address */
#define FTFC_BASE_ADDR                           (0x40020000u)
/** Peripheral FTFC base pointer */
#define FTFC                                     ((FTFC_Type *)FTFC_BASE_ADDR)

#define FTFC_FSTAT_CCIF_MASK                     0x80u
#define FTFC_FSTAT_ACCERR_MASK                   0x20u
#define FTFC_FSTAT_FPVIOL_MASK                   0x10u
#define FTFC_FSTAT_RDCOLERR_MASK                 0x40u
#define FTFC_FSTAT_MGSTAT0_MASK                  0x1u

// Define error codes
#define FLASH_OK 0
#define FLASH_ERROR_PROGRAM 1
#define FLASH_ERROR_ERASE 2

#endif
