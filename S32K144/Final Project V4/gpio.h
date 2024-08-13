/***********************************************************************
* File name: gpio.h
* Description: GPIO Configuration file of MCU module
* Version: 1.0
* Date:
*               8/7/2024: New
 ***********************************************************************/
#ifndef GPIO_H
#define GPIO_H

/***********************************************************************
 *         Inclusion
 ***********************************************************************/
#include "Gpio_Registers.h"

/***********************************************************************
 *         Function Prototype Denifition
 ***********************************************************************/
/*!
 * @brief Initializes the GPIO
 * @Description: This function configures the pins with the options provided in the
 * provided structure.
 * @param[in] pinCount The number of configured pins in structure
 * @param[in] config The configuration structure
 * @return 
 */
void Gpio_Init(const Gpio_ConfigType* ConfigPtr);

/*!
 * @brief Writes a value to the specified output pin
 *
 * @param[in] pGPIOx Pointer to GPIO base address
 * @param[in] PinNumber Pin number to be written to
 * @param[in] value Value to write to the pin (0 or 1)
 */
void GPIO_WriteToOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber, unsigned char value);

/*!
 * @brief Sets the specified output pin
 *
 * @param[in] pGPIOx Pointer to GPIO base address
 * @param[in] PinNumber Pin number to be set
 */
void GPIO_SetOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber);

/*!
 * @brief Resets the specified output pin
 *
 * @param[in] pGPIOx Pointer to GPIO base address
 * @param[in] PinNumber Pin number to be reset
 */
void GPIO_ResetOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber);

/*!
 * @brief Toggles the specified output pin
 *
 * @param[in] pGPIOx Pointer to GPIO base address
 * @param[in] PinNumber Pin number to be toggled
 */
void GPIO_ToggleOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber);

/*!
 * @brief Reads the value from the specified input pin
 *
 * @param[in] pGPIOx Pointer to GPIO base address
 * @param[in] PinNumber Pin number to be read
 * @return Value of the pin (0 or 1)
 */
unsigned char GPIO_ReadFromInputPin(GPIO_Type *pGPIOx, unsigned char PinNumber);
#endif
