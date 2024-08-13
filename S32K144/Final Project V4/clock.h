#ifndef CLOCK_CONF_H
#define CLOCK_CONF_H

/* SCG - Peripheral instance base addresses */
/** Peripheral SCG base address */
#define SOSCCSR                                 *(volatile unsigned int*)(0x40064000u + 0x100U)
#define SOSCDIV                                 *(volatile unsigned int*)(0x40064000u + 0x104U)
#define SOSCCFG                                 *(volatile unsigned int*)(0x40064000u + 0x108U)

#define SPLLCSR                                 *(volatile unsigned int*)(0x40064000u + 0x600U)
#define SPLLDIV                                 *(volatile unsigned int*)(0x40064000u + 0x604U)
#define SPLLCFG                                 *(volatile unsigned int*)(0x40064000u + 0x608U)

#define SCGCSR                                  *(volatile unsigned int*)(0x40064000u + 0x10)
#define SCGRCCR                                 *(volatile unsigned int*)(0x40064000u + 0x14)
#define SCGVCCR                                 *(volatile unsigned int*)(0x40064000u + 0x18)

/*********************************************
						Function Prototype 
*********************************************/
void SOSC_Init(void);
void SPLL_160Mhz_init(void);
void NormalRUNmode_80MHz(void);

#endif
