#ifndef NVIC_H
#define NVIC_H

/***********************************************************************
 *         Inclusion
 ***********************************************************************/
#include "nvic_register.h"

/***********************************************************************
 *         Function Prototype Denifition
 ***********************************************************************/
/*!
 * @brief   Enable Interrupt
 * @details Enables a device specific interrupt in the NVIC interrupt controller.
 * @param[in] IRQ_number: Device specific interrupt number.
 * @return 
 */
void NVIC_EnableInterrupt(const IRQn_Type IRQ_number);

/*!
 * @brief   Disable Interrupt
 * @details Disable interrupt device specific interrupt number in the NVIC interrupt controller.
 * @param[in] IRQ_number: Device specific interrupt number. 
 * @return 
 */
void NVIC_DisableInterrupt(IRQn_Type IRQ_number);

/*!
 * @brief Clear pending flag
 * @details Clear pending flag of device specific interrupt number in the NVIC interrupt controller.
 * @param[in] IRQ_number: Device specific interrupt number.
 * @return 
 */
void NVIC_ClearPendingFlag(IRQn_Type IRQ_number);

/*!
 * @brief Set priority
  \details Sets the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
 * @param[in] IRQ_number: The order of IRQn of s32k144
 * @param[in] priority: The priority of IRQn provided
 * @return 
 */
void NVIC_SetPriority(IRQn_Type IRQn, unsigned char priority);
#endif
