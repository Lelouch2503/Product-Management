#ifndef _LPUART_REG_H_
#define _LPUART_REG_H_

#include "main.h"


/***********************************************************************
 *         Typedef Denifition
 ***********************************************************************/
/** LPUART - Size of Registers Arrays */
/** LPUART - Register Layout Typedef */
typedef struct {
  volatile const  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
  volatile const  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
  volatile uint32_t GLOBAL;                            /**< LPUART Global Register, offset: 0x8 */
  volatile uint32_t PINCFG;                            /**< LPUART Pin Configuration Register, offset: 0xC */
  volatile uint32_t BAUD;                              /**< LPUART Baud Rate Register, offset: 0x10 */
  volatile uint32_t STAT;                              /**< LPUART Status Register, offset: 0x14 */
  volatile uint32_t CTRL;                              /**< LPUART Control Register, offset: 0x18 */
  volatile uint32_t DATA;                              /**< LPUART Data Register, offset: 0x1C */
  volatile uint32_t MATCH;                             /**< LPUART Match Address Register, offset: 0x20 */
  volatile uint32_t MODIR;                             /**< LPUART Modem IrDA Register, offset: 0x24 */
  volatile uint32_t FIFO;                              /**< LPUART FIFO Register, offset: 0x28 */
  volatile uint32_t WATER;                             /**< LPUART Watermark Register, offset: 0x2C */
} LPUART_Type;

typedef enum {
    LPuart_irq0 = 0,
    LPuart_irq1,
    LPuart_irq2
} LPUART_irq;

typedef enum {
	CLOCK_SOSC = 0,
	CLOCK_SIRC,
	CLOCK_FIRC,
	CLOCK_SPLL
} Clock_Source;


/***********************************************************************
 *         Macro Denifition
 ***********************************************************************/

#define LPUART_INSTANCE_COUNT                    (3u)

#define LPUART0_BASE_ADDR                            (0x4006A000u)
#define LPUART0                                  ((LPUART_Type *)LPUART0_BASE_ADDR)
#define LPUART1_BASE_ADDR                             (0x4006B000u)
#define LPUART1                                  ((LPUART_Type *)LPUART1_BASE_ADDR)
#define LPUART2_BASE_ADDR                             (0x4006C000u)
#define LPUART2                                  ((LPUART_Type *)LPUART2_BASE_ADDR)

#define SOSC_CLK_FREQ   8000000U  // Example frequency for SOSC
#define SIRC_CLK_FREQ   8000000U  // Example frequency for SIRC
#define FIRC_CLK_FREQ   48000000U // Example frequency for FIRC
#define SPLL_CLK_FREQ   160000000U// Example frequency for SPLL

#define LPUART_BAUD_SBR_MASK                     0x1FFFu
#define LPUART_BAUD_SBR_SHIFT                    0u
#define LPUART_BAUD_SBR_WIDTH                    13u
#define LPUART_BAUD_SBR(x)                       (((uint32_t)(((uint32_t)(x))<<LPUART_BAUD_SBR_SHIFT))&LPUART_BAUD_SBR_MASK)
#define LPUART_CTRL_RE_MASK                      0x40000u
#define LPUART_CTRL_TE_MASK                      0x80000u
#define LPUART_CTRL_RIE_MASK                     0x200000u
#define LPUART_STAT_TDRE_MASK                    0x800000u
#define LPUART_STAT_RDRF_MASK                    0x200000u

#endif
