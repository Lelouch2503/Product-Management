#include "gpio.h"

/*! FUNCTION**********************************************************************
 *
 * @FunctionName : Gpio_Init
 * @Description  : This function configures the pins with the options provided in the
 * provided structure.
 *
 * @Implements   : Gpio_Init_Activity
 *END**************************************************************************/
void Gpio_Init(const Gpio_ConfigType* ConfigPtr)
{
	/* Check parameter */
	pinMode Mode = ConfigPtr->GPIO_PinMode; // Get pin mode from configuration
	unsigned char Pin = ConfigPtr->GPIO_PinNumber; // Get pin number from configuration
	
	PORT_PCR_TYPE * pcrRegValue  = ConfigPtr->portBase;
	unsigned char muxMode = ConfigPtr->muxMode;
	pcrRegValue->PORT_PCRn[Pin] |= (unsigned int)(muxMode << 8u);
	
	GPIO_Type * gpioRegValue = ConfigPtr->gpioBase; // Get GPIO base address from configuration

	// Configure the pin as input or output based on mode
	switch(Mode)
	{
		case INPUT:
			gpioRegValue->PDDR &= ~(1 << Pin); // Set pin as input
		break;
		
		case OUTPUT:
			gpioRegValue->PDDR |= (1 << Pin); // Set pin as output
		break;
		default:
		break;
	}
}

/*! FUNCTION**********************************************************************
 *
 * @FunctionName : GPIO_WriteToOutputPin
 * @Description  : Writes a value to the specified output pin
 *
 * @Implements   : GPIO_WriteToOutputPin_Activity
 *END**************************************************************************/
void GPIO_WriteToOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber, unsigned char value)
{
	if(value)
	{
		pGPIOx->PDOR |= (1 << PinNumber); // Set pin high
	}
	else
	{
		pGPIOx->PDOR &= ~(1 << PinNumber); // Set pin low
	}
}

/*! FUNCTION**********************************************************************
 *
 * @FunctionName : GPIO_SetOutputPin
 * @Description  : Sets the specified output pin
 *
 * @Implements   : GPIO_SetOutputPin_Activity
 *END**************************************************************************/
void GPIO_SetOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber)
{
	pGPIOx->PDOR |= (1 << PinNumber); // Set pin high
}

/*! FUNCTION**********************************************************************
 *
 * @FunctionName : GPIO_ResetOutputPin
 * @Description  : Resets the specified output pin
 *
 * @Implements   : GPIO_ResetOutputPin_Activity
 *END**************************************************************************/
void GPIO_ResetOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber)
{
	pGPIOx->PDOR &= ~(1 << PinNumber); // Set pin low
}

/*! FUNCTION**********************************************************************
 *
 * @FunctionName : GPIO_ToggleOutputPin
 * @Description  : Toggles the specified output pin
 *
 * @Implements   : GPIO_ToggleOutputPin_Activity
 *END**************************************************************************/
void GPIO_ToggleOutputPin(GPIO_Type *pGPIOx, unsigned char PinNumber)
{
	pGPIOx->PDOR ^= (1u << PinNumber); // Toggle pin state
}

/*! FUNCTION**********************************************************************
 *
 * @FunctionName : GPIO_ReadFromInputPin
 * @Description  : Reads the value from the specified input pin
 *
 * @Implements   : GPIO_ReadFromInputPin_Activity
 *END**************************************************************************/
unsigned char GPIO_ReadFromInputPin(GPIO_Type *pGPIOx, unsigned char PinNumber)
{
	return ((pGPIOx->PDIR >> PinNumber) & 0x1); // Read pin state
}
