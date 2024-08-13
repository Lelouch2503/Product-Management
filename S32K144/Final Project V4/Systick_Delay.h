#ifndef _SYSTICK_DELAY_H_
#define _SYSTICK_DELAY_H_

#include "stdint.h"

#define CLK_CORE         (80000000u)

/** S32_SysTick - Size of Registers Arrays */

/** S32_SysTick - Register Layout Typedef */
typedef struct {
  volatile uint32_t CSR;                               /**< SysTick Control and Status Register, offset: 0x0 */
  volatile uint32_t RVR;                               /**< SysTick Reload Value Register, offset: 0x4 */
  volatile uint32_t CVR;                               /**< SysTick Current Value Register, offset: 0x8 */
  volatile const  uint32_t CALIB;                             /**< SysTick Calibration Value Register, offset: 0xC */
} SysTick_Type;


/* S32_SysTick - Peripheral instance base addresses */
/** Peripheral S32_SysTick base address */
#define S32_SysTick_BASE                         (0xE000E010u)
/** Peripheral S32_SysTick base pointer */
#define S32_SysTick                              ((SysTick_Type *)S32_SysTick_BASE)

void DelayMillis(void);
void initSysTick(void) ;
void delay_ms(unsigned long t);

#endif
