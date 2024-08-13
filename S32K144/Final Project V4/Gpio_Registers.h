/***********************************************************************
* File name: Gpio_Registers.h
* Description: Include structure type, Peripheral GPIOx base address for configuration
* Version: 2.0
* Update: PORT_PCR_TYPE, muxMode, pinNumber
* Date:
*               20/7/2024: New update
 ***********************************************************************/
#ifndef GPIO_REGISTER_H
#define GPIO_REGISTER_H


/***********************************************************************
 *         Macro Denifition
 ***********************************************************************/
/** Peripheral GPIOA base address */
#define GPIOA_BASE                               (0x400FF000u)

/** Peripheral GPIOA base pointer */
#define GPIOA    ((GPIO_Type *)GPIOA_BASE)

/** Peripheral GPIOC base address */
#define GPIOB_BASE                               (0x400FF040u)

/** Peripheral GPIOC base pointer */
#define GPIOB    ((GPIO_Type *)GPIOB_BASE)

/** Peripheral GPIOC base address */
#define GPIOC_BASE                               (0x400FF080u)

/** Peripheral GPIOC base pointer */
#define GPIOC    ((GPIO_Type *)GPIOC_BASE)

/** Peripheral GPIOD base address */
#define GPIOD_BASE                               (0x400FF0C0u)

/** Peripheral GPIOD base pointer */
#define GPIOD    ((GPIO_Type *)GPIOD_BASE)



#define PORT_INSTANCE_COUNT                      (5u)

/** PORT - Size of Registers Arrays */
#define PORT_PCR_COUNT                           (32u)

/***********************************************************************
 *         Typedef Denifition
 ***********************************************************************/
/**
  \brief  Structure type to access the GPIO.
 */
typedef struct {
  volatile unsigned int PDOR;
	volatile unsigned int PSOR;
	volatile unsigned int PCOR;
	volatile unsigned int PTOR;
	volatile const unsigned int PDIR;
	volatile unsigned int PDDR;
	volatile unsigned int PIDR;
} GPIO_Type;

typedef struct {
	volatile unsigned int PORT_PCRn[PORT_PCR_COUNT];
} PORT_PCR_TYPE;

/** Pin Mode */
typedef enum {
	INPUT = 0u,
	OUTPUT,
	NONE
} pinMode;

/** Pin Number */
typedef enum {
    PIN0 = 0u,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15,
    PIN16,
    PIN17,
    PIN18,
    PIN19,
    PIN20,
    PIN21,
    PIN22,
    PIN23,
    PIN24,
    PIN25,
    PIN26,
    PIN27,
    PIN28,
    PIN29,
    PIN30,
    PIN31
} pinNumber;

/** Pin Mux Mode */
typedef enum {
	DISABLE = 0u,
	GPIO,
	MUXALT2,
	MUXALT3,
	MUXALT4,
	MUXALT5,
	MUXALT6
} muxMode;

#pragma pack(push, 1)  // Set packing alignment to 1 byte boundary
typedef struct {
		PORT_PCR_TYPE     *      portBase;
    GPIO_Type         *      gpioBase;                  /*!< Gpio base pointer.  */
		muxMode                  muxMode;
    pinNumber                GPIO_PinNumber;            /*!< Pin number. */
    pinMode                  GPIO_PinMode;              /*!< Pin_mode */
} Gpio_ConfigType;
#pragma pack(pop)  // Reset to default packing alignment

/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE                               (0x40049000u)
/** Peripheral PORTA base pointer */
#define PORTA                                    ((PORT_PCR_TYPE *)PORTA_BASE)
/** Peripheral PORTB base address */
#define PORTB_BASE                               (0x4004A000u)
/** Peripheral PORTB base pointer */
#define PORTB                                    ((PORT_PCR_TYPE *)PORTB_BASE)
/** Peripheral PORTC base address */
#define PORTC_BASE                               (0x4004B000u)
/** Peripheral PORTC base pointer */
#define PORTC                                    ((PORT_PCR_TYPE *)PORTC_BASE)
/** Peripheral PORTD base address */
#define PORTD_BASE                               (0x4004C000u)
/** Peripheral PORTD base pointer */
#define PORTD                                    ((PORT_PCR_TYPE *)PORTD_BASE)
/** Peripheral PORTE base address */
#define PORTE_BASE                               (0x4004D000u)
/** Peripheral PORTE base pointer */
#define PORTE                                    ((PORT_PCR_TYPE *)PORTE_BASE)

/**End Of File************************************************************/
#endif
