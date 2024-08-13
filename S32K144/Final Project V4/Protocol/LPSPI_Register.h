/***********************************************************************
* File name: gpio.h
* Description: GPIO Configuration file of MCU module
* Version: 1.0
* Date:
*               8/7/2024: New
 ***********************************************************************/
#ifndef LPSPI_REGISTER_H
#define LPSPI_REGISTER_H

/***********************************************************************
 *         Inclusion
 ***********************************************************************/
#include "main.h"


/***********************************************************************
 *         Typedef Denifition
 ***********************************************************************/
/** LPSPI - Size of Registers Arrays */

/** LPSPI - Register Layout Typedef */
typedef struct {
  volatile const  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
  volatile const  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
       uint8_t RESERVED_0[8];
  volatile uint32_t CR;                                /**< Control Register, offset: 0x10 */
  volatile uint32_t SR;                                /**< Status Register, offset: 0x14 */
  volatile uint32_t IER;                               /**< Interrupt Enable Register, offset: 0x18 */
  volatile uint32_t DER;                               /**< DMA Enable Register, offset: 0x1C */
  volatile uint32_t CFGR0;                             /**< Configuration Register 0, offset: 0x20 */
  volatile uint32_t CFGR1;                             /**< Configuration Register 1, offset: 0x24 */
       uint8_t RESERVED_1[8];
  volatile uint32_t DMR0;                              /**< Data Match Register 0, offset: 0x30 */
  volatile uint32_t DMR1;                              /**< Data Match Register 1, offset: 0x34 */
       uint8_t RESERVED_2[8];
  volatile uint32_t CCR;                               /**< Clock Configuration Register, offset: 0x40 */
       uint8_t RESERVED_3[20];
  volatile uint32_t FCR;                               /**< FIFO Control Register, offset: 0x58 */
  volatile const  uint32_t FSR;                               /**< FIFO Status Register, offset: 0x5C */
  volatile uint32_t TCR;                               /**< Transmit Command Register, offset: 0x60 */
  volatile  uint32_t TDR;                               /**< Transmit Data Register, offset: 0x64 */
       uint8_t RESERVED_4[8];
  volatile const  uint32_t RSR;                               /**< Receive Status Register, offset: 0x70 */
  volatile const  uint32_t RDR;                               /**< Receive Data Register, offset: 0x74 */
} LPSPI_Type;

/***********************************************************************
 *                          Macro Denifition
 ***********************************************************************/

 /** Number of instances of the LPSPI module. */
#define LPSPI_INSTANCE_COUNT                     (3u)


/* LPSPI - Peripheral instance base addresses */
/** Peripheral LPSPI0 base address */
/* LPSPI - Peripheral instance base addresses */
/** Peripheral LPSPI0 base address */
#define LPSPI0_BASE                              (0x4002C000u)
/** Peripheral LPSPI0 base pointer */
#define LPSPI0                                   ((LPSPI_Type *)LPSPI0_BASE)
#define LPSPI1_BASE                              (0x4002D000u)
/** Peripheral LPSPI1 base pointer */
#define LPSPI1                                   ((LPSPI_Type *)LPSPI1_BASE)

#define LPSPI_SR_TDF_MASK                        0x1u
#define LPSPI_SR_TDF_SHIFT                       0u
#define LPSPI_SR_TCF_SHIFT                       10u
#define LPSPI_SR_RDF_MASK                        0x2u
#define LPSPI_SR_RDF_SHIFT                       1u
#define LPSPI_SR_TCF_MASK                        0x400u
#define LPSPI_CR_MEN_MASK                        0x1u
#define LPSPI_CR_DBGEN_MASK                      0x8u

/* CCR Bit Fields */
#define LPSPI_CCR_SCKDIV_MASK                    0xFFu
#define LPSPI_CCR_SCKDIV_SHIFT                   0u
#define LPSPI_CCR_SCKDIV_WIDTH                   8u
#define LPSPI_CCR_SCKDIV(x)                      (((uint32_t)(((uint32_t)(x))<<LPSPI_CCR_SCKDIV_SHIFT))&LPSPI_CCR_SCKDIV_MASK)
#define LPSPI_CCR_DBT_MASK                       0xFF00u
#define LPSPI_CCR_DBT_SHIFT                      8u
#define LPSPI_CCR_DBT_WIDTH                      8u
#define LPSPI_CCR_DBT(x)                         (((uint32_t)(((uint32_t)(x))<<LPSPI_CCR_DBT_SHIFT))&LPSPI_CCR_DBT_MASK)
#define LPSPI_CCR_PCSSCK_MASK                    0xFF0000u
#define LPSPI_CCR_PCSSCK_SHIFT                   16u
#define LPSPI_CCR_PCSSCK_WIDTH                   8u
#define LPSPI_CCR_PCSSCK(x)                      (((uint32_t)(((uint32_t)(x))<<LPSPI_CCR_PCSSCK_SHIFT))&LPSPI_CCR_PCSSCK_MASK)
#define LPSPI_CCR_SCKPCS_MASK                    0xFF000000u
#define LPSPI_CCR_SCKPCS_SHIFT                   24u
#define LPSPI_CCR_SCKPCS_WIDTH                   8u
#define LPSPI_CCR_SCKPCS(x)                      (((uint32_t)(((uint32_t)(x))<<LPSPI_CCR_SCKPCS_SHIFT))&LPSPI_CCR_SCKPCS_MASK)

/* FCR Bit Fields */
#define LPSPI_FCR_TXWATER_MASK                   0x3u
#define LPSPI_FCR_TXWATER_SHIFT                  0u
#define LPSPI_FCR_TXWATER_WIDTH                  2u
#define LPSPI_FCR_TXWATER(x)                     (((uint32_t)(((uint32_t)(x))<<LPSPI_FCR_TXWATER_SHIFT))&LPSPI_FCR_TXWATER_MASK)
#define LPSPI_FCR_RXWATER_MASK                   0x30000u
#define LPSPI_FCR_RXWATER_SHIFT                  16u
#define LPSPI_FCR_RXWATER_WIDTH                  2u
#define LPSPI_FCR_RXWATER(x)                     (((uint32_t)(((uint32_t)(x))<<LPSPI_FCR_RXWATER_SHIFT))&LPSPI_FCR_RXWATER_MASK)
/* TCR Bit Fields */
#define LPSPI_TCR_FRAMESZ_MASK                   0xFFFu
#define LPSPI_TCR_FRAMESZ_SHIFT                  0u
#define LPSPI_TCR_FRAMESZ_WIDTH                  12u
#define LPSPI_TCR_FRAMESZ(x)                     (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_FRAMESZ_SHIFT))&LPSPI_TCR_FRAMESZ_MASK)
#define LPSPI_TCR_WIDTH_MASK                     0x30000u
#define LPSPI_TCR_WIDTH_SHIFT                    16u
#define LPSPI_TCR_WIDTH_WIDTH                    2u
#define LPSPI_TCR_WIDTH(x)                       (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_WIDTH_SHIFT))&LPSPI_TCR_WIDTH_MASK)
#define LPSPI_TCR_TXMSK_MASK                     0x40000u
#define LPSPI_TCR_TXMSK_SHIFT                    18u
#define LPSPI_TCR_TXMSK_WIDTH                    1u
#define LPSPI_TCR_TXMSK(x)                       (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_TXMSK_SHIFT))&LPSPI_TCR_TXMSK_MASK)
#define LPSPI_TCR_RXMSK_MASK                     0x80000u
#define LPSPI_TCR_RXMSK_SHIFT                    19u
#define LPSPI_TCR_RXMSK_WIDTH                    1u
#define LPSPI_TCR_RXMSK(x)                       (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_RXMSK_SHIFT))&LPSPI_TCR_RXMSK_MASK)
#define LPSPI_TCR_CONTC_MASK                     0x100000u
#define LPSPI_TCR_CONTC_SHIFT                    20u
#define LPSPI_TCR_CONTC_WIDTH                    1u
#define LPSPI_TCR_CONTC(x)                       (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_CONTC_SHIFT))&LPSPI_TCR_CONTC_MASK)
#define LPSPI_TCR_CONT_MASK                      0x200000u
#define LPSPI_TCR_CONT_SHIFT                     21u
#define LPSPI_TCR_CONT_WIDTH                     1u
#define LPSPI_TCR_CONT(x)                        (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_CONT_SHIFT))&LPSPI_TCR_CONT_MASK)
#define LPSPI_TCR_BYSW_MASK                      0x400000u
#define LPSPI_TCR_BYSW_SHIFT                     22u
#define LPSPI_TCR_BYSW_WIDTH                     1u
#define LPSPI_TCR_BYSW(x)                        (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_BYSW_SHIFT))&LPSPI_TCR_BYSW_MASK)
#define LPSPI_TCR_LSBF_MASK                      0x800000u
#define LPSPI_TCR_LSBF_SHIFT                     23u
#define LPSPI_TCR_LSBF_WIDTH                     1u
#define LPSPI_TCR_LSBF(x)                        (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_LSBF_SHIFT))&LPSPI_TCR_LSBF_MASK)
#define LPSPI_TCR_PCS_MASK                       0x3000000u
#define LPSPI_TCR_PCS_SHIFT                      24u
#define LPSPI_TCR_PCS_WIDTH                      2u
#define LPSPI_TCR_PCS(x)                         (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_PCS_SHIFT))&LPSPI_TCR_PCS_MASK)
#define LPSPI_TCR_PRESCALE_MASK                  0x38000000u
#define LPSPI_TCR_PRESCALE_SHIFT                 27u
#define LPSPI_TCR_PRESCALE_WIDTH                 3u
#define LPSPI_TCR_PRESCALE(x)                    (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_PRESCALE_SHIFT))&LPSPI_TCR_PRESCALE_MASK)
#define LPSPI_TCR_CPHA_MASK                      0x40000000u
#define LPSPI_TCR_CPHA_SHIFT                     30u
#define LPSPI_TCR_CPHA_WIDTH                     1u
#define LPSPI_TCR_CPHA(x)                        (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_CPHA_SHIFT))&LPSPI_TCR_CPHA_MASK)
#define LPSPI_TCR_CPOL_MASK                      0x80000000u
#define LPSPI_TCR_CPOL_SHIFT                     31u
#define LPSPI_TCR_CPOL_WIDTH                     1u
#define LPSPI_TCR_CPOL(x)                        (((uint32_t)(((uint32_t)(x))<<LPSPI_TCR_CPOL_SHIFT))&LPSPI_TCR_CPOL_MASK)
/* CFGR1 Bit Fields */
#define LPSPI_CFGR1_MASTER_MASK                  0x1u
#define LPSPI_CFGR1_MASTER_SHIFT                 0u
#define LPSPI_CFGR1_MASTER_WIDTH                 1u
#define LPSPI_CFGR1_MASTER(x)                    (((uint32_t)(((uint32_t)(x))<<LPSPI_CFGR1_MASTER_SHIFT))&LPSPI_CFGR1_MASTER_MASK)
#define LPSPI_CFGR1_SAMPLE_MASK                  0x2u
#define LPSPI_CFGR1_SAMPLE_SHIFT                 1u
#define LPSPI_CFGR1_SAMPLE_WIDTH                 1u
#define LPSPI_CFGR1_SAMPLE(x)                    (((uint32_t)(((uint32_t)(x))<<LPSPI_CFGR1_SAMPLE_SHIFT))&LPSPI_CFGR1_SAMPLE_MASK)
#define LPSPI_CFGR1_AUTOPCS_MASK                 0x4u
#define LPSPI_CFGR1_AUTOPCS_SHIFT                2u
#define LPSPI_CFGR1_AUTOPCS_WIDTH                1u
#define LPSPI_CFGR1_AUTOPCS(x)                   (((uint32_t)(((uint32_t)(x))<<LPSPI_CFGR1_AUTOPCS_SHIFT))&LPSPI_CFGR1_AUTOPCS_MASK)
#define LPSPI_CFGR1_NOSTALL_MASK                 0x8u
#define LPSPI_CFGR1_NOSTALL_SHIFT                3u
#define LPSPI_CFGR1_NOSTALL_WIDTH                1u
#define LPSPI_CFGR1_NOSTALL(x)                   (((uint32_t)(((uint32_t)(x))<<LPSPI_CFGR1_NOSTALL_SHIFT))&LPSPI_CFGR1_NOSTALL_MASK)
#define LPSPI_CFGR1_PCSPOL_MASK                  0xF00u
#define LPSPI_CFGR1_PCSPOL_SHIFT                 8u
#define LPSPI_CFGR1_PCSPOL_WIDTH                 4u
#define LPSPI_CFGR1_PCSPOL(x)                    (((uint32_t)(((uint32_t)(x))<<LPSPI_CFGR1_PCSPOL_SHIFT))&LPSPI_CFGR1_PCSPOL_MASK)
#define LPSPI_CFGR1_MATCFG_MASK                  0x70000u
#define LPSPI_CFGR1_MATCFG_SHIFT                 16u
#define LPSPI_CFGR1_MATCFG_WIDTH                 3u
#define LPSPI_CFGR1_MATCFG(x)                    (((uint32_t)(((uint32_t)(x))<<LPSPI_CFGR1_MATCFG_SHIFT))&LPSPI_CFGR1_MATCFG_MASK)
#define LPSPI_CFGR1_PINCFG_MASK                  0x3000000u
#define LPSPI_CFGR1_PINCFG_SHIFT                 24u
#define LPSPI_CFGR1_PINCFG_WIDTH                 2u
#define LPSPI_CFGR1_PINCFG(x)                    (((uint32_t)(((uint32_t)(x))<<LPSPI_CFGR1_PINCFG_SHIFT))&LPSPI_CFGR1_PINCFG_MASK)
#define LPSPI_CFGR1_OUTCFG_MASK                  0x4000000u
#define LPSPI_CFGR1_OUTCFG_SHIFT                 26u
#define LPSPI_CFGR1_OUTCFG_WIDTH                 1u
#define LPSPI_CFGR1_OUTCFG(x)                    (((uint32_t)(((uint32_t)(x))<<LPSPI_CFGR1_OUTCFG_SHIFT))&LPSPI_CFGR1_OUTCFG_MASK)
#define LPSPI_CFGR1_PCSCFG_MASK                  0x8000000u
#define LPSPI_CFGR1_PCSCFG_SHIFT                 27u
#define LPSPI_CFGR1_PCSCFG_WIDTH                 1u
#define LPSPI_CFGR1_PCSCFG(x)                    (((uint32_t)(((uint32_t)(x))<<LPSPI_CFGR1_PCSCFG_SHIFT))&LPSPI_CFGR1_PCSCFG_MASK)

/* TDR Bit Fields */
#define LPSPI_TDR_DATA_MASK                      0xFFFFFFFFu
#define LPSPI_TDR_DATA_SHIFT                     0u
#define LPSPI_TDR_DATA_WIDTH                     32u
#define LPSPI_TDR_DATA(x)                        (((uint32_t)(((uint32_t)(x))<<LPSPI_TDR_DATA_SHIFT))&LPSPI_TDR_DATA_MASK)
#endif
