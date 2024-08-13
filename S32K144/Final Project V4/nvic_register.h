#ifndef NVIC_REGISTERS_H
#define NVIC_REGISTERS_H

#include "stdint.h"
/***********************************************************************
 *         Typedef Denifition
 ***********************************************************************/
typedef enum {
	  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M4 SV Hard Fault Interrupt */
  MemoryManagement_IRQn        = -12,              /**< Cortex-M4 Memory Management Interrupt */
  BusFault_IRQn                = -11,              /**< Cortex-M4 Bus Fault Interrupt */
  UsageFault_IRQn              = -10,              /**< Cortex-M4 Usage Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M4 SV Call Interrupt */
  DebugMonitor_IRQn            = -4,               /**< Cortex-M4 Debug Monitor Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M4 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M4 System Tick Interrupt */
	
  /* Device specific interrupts */
  DMA0_IRQn                    = 0,                /**< DMA channel 0 transfer complete */
  DMA1_IRQn                    = 1,                /**< DMA channel 1 transfer complete */
  DMA2_IRQn                    = 2,                /**< DMA channel 2 transfer complete */
  DMA3_IRQn                    = 3,                /**< DMA channel 3 transfer complete */
  DMA4_IRQn                    = 4,                /**< DMA channel 4 transfer complete */
  DMA5_IRQn                    = 5,                /**< DMA channel 5 transfer complete */
  DMA6_IRQn                    = 6,                /**< DMA channel 6 transfer complete */
  DMA7_IRQn                    = 7,                /**< DMA channel 7 transfer complete */
  DMA8_IRQn                    = 8,                /**< DMA channel 8 transfer complete */
  DMA9_IRQn                    = 9,                /**< DMA channel 9 transfer complete */
  DMA10_IRQn                   = 10,               /**< DMA channel 10 transfer complete */
  DMA11_IRQn                   = 11,               /**< DMA channel 11 transfer complete */
  DMA12_IRQn                   = 12,               /**< DMA channel 12 transfer complete */
  DMA13_IRQn                   = 13,               /**< DMA channel 13 transfer complete */
  DMA14_IRQn                   = 14,               /**< DMA channel 14 transfer complete */
  DMA15_IRQn                   = 15,               /**< DMA channel 15 transfer complete */
  DMA_Error_IRQn               = 16,               /**< DMA error interrupt channels 0-15 */
  MCM_IRQn                     = 17,               /**< FPU sources */
  FTFM_IRQn                    = 18,               /**< FTFM Command complete */
  Read_Collision_IRQn          = 19,               /**< FTFM Read collision */
  LVD_LVW_IRQn                 = 20,               /**< PMC Low voltage detect interrupt */
  FTFM_Fault_IRQn              = 21,               /**< FTFM Double bit fault detect */
  WDOG_EWM_IRQn                = 22,               /**< Interrupt request out before WDOG reset out, EWM output as interrupt */
  RCM_IRQn                     = 23,               /**< RCM Asynchronous Interrupt */
  LPI2C0_Master_IRQn           = 24,               /**< LPI2C0 Master Interrupt */
  LPI2C0_Slave_IRQn            = 25,               /**< LPI2C0 Slave Interrupt */
  LPSPI0_IRQn                  = 26,               /**< LPSPI0 Interrupt */
  LPSPI1_IRQn                  = 27,               /**< LPSPI1 Interrupt */
  LPSPI2_IRQn                  = 28,               /**< LPSPI2 Interrupt */
  LPUART0_RxTx_IRQn            = 31,               /**< LPUART0 Transmit / Receive Interrupt / Error / Overrun */
  LPUART1_RxTx_IRQn            = 33,               /**< LPUART1 Transmit / Receive Interrupt / Error / Overrun */
  LPUART2_RxTx_IRQn            = 35,               /**< LPUART2 Transmit / Receive Interrupt / Error / Overrun */
  ADC0_IRQn                    = 39,               /**< ADC0 interrupt request */
  ADC1_IRQn                    = 40,               /**< ADC1 interrupt request */
  CMP0_IRQn                    = 41,               /**< CMP0 interrupt request */
  ERM_single_fault_IRQn        = 44,               /**< ERM single bit error correction */
  ERM_double_fault_IRQn        = 45,               /**< ERM double bit error non-correctable */
  RTC_IRQn                     = 46,               /**< RTC alarm interrupt */
  RTC_Seconds_IRQn             = 47,               /**< RTC seconds interrupt */
  LPIT0_Ch0_IRQn               = 48,               /**< LPIT0 channel 0 overflow interrupt */
  LPIT0_Ch1_IRQn               = 49,               /**< LPIT0 channel 1 overflow interrupt */
  LPIT0_Ch2_IRQn               = 50,               /**< LPIT0 channel 2 overflow interrupt */
  LPIT0_Ch3_IRQn               = 51,               /**< LPIT0 channel 3 overflow interrupt */
  PDB0_IRQn                    = 52,               /**< PDB0 interrupt */
  SCG_IRQn                     = 57,               /**< SCG bus interrupt request */
  LPTMR0_IRQn                  = 58,               /**< LPTIMER interrupt request */
  PORTA_IRQn                   = 59,               /**< Port A pin detect interrupt */
  PORTB_IRQn                   = 60,               /**< Port B pin detect interrupt */
  PORTC_IRQn                   = 61,               /**< Port C pin detect interrupt */
  PORTD_IRQn                   = 62,               /**< Port D pin detect interrupt */
  PORTE_IRQn                   = 63,               /**< Port E pin detect interrupt */
  SWI_IRQn                     = 64,               /**< Software interrupt */
  PDB1_IRQn                    = 68,               /**< PDB1 interrupt */
  FLEXIO_IRQn                  = 69,               /**< Software interrupt */
  CAN0_ORed_IRQn               = 78,               /**< CAN0 OR'ed Bus in Off State. */
  CAN0_Error_IRQn              = 79,               /**< CAN0 Interrupt indicating that errors were detected on the CAN bus */
  CAN0_Wake_Up_IRQn            = 80,               /**< CAN0 Interrupt asserted when Pretended Networking operation is enabled, and a valid message matches the selected filter criteria during Low Power mode */
  CAN0_ORed_0_15_MB_IRQn       = 81,               /**< CAN0 OR'ed Message buffer (0-15) */
  CAN0_ORed_16_31_MB_IRQn      = 82,               /**< CAN0 OR'ed Message buffer (16-31) */
  CAN0_ORed_32_47_MB_IRQn      = 83,               /**< CAN0 OR'ed Message buffer (32-47) */
  CAN0_ORed_48_63_MB_IRQn      = 84,               /**< CAN0 OR'ed Message buffer (32-47) */
  CAN1_ORed_IRQn               = 85,               /**< CAN1 OR'ed Bus in Off State. */
  CAN1_Error_IRQn              = 86,               /**< CAN1 Interrupt indicating that errors were detected on the CAN bus */
  CAN1_ORed_0_15_MB_IRQn       = 88,               /**< CAN1 OR'ed Message buffer (0-15) */
  CAN1_ORed_16_31_MB_IRQn      = 89,               /**< CAN1 OR'ed Message buffer (16-31) */
  CAN1_ORed_32_47_MB_IRQn      = 90,               /**< CAN1 OR'ed Message buffer (32-47) */
  CAN1_ORed_48_63_MB_IRQn      = 91,               /**< CAN1 OR'ed Message buffer (32-47) */
  FTM0_Ch0_Ch1_IRQn            = 99,               /**< FTM0 Channel 0 and 1 interrupt */
  FTM0_Ch2_Ch3_IRQn            = 100,              /**< FTM0 Channel 2 and 3 interrupt */
  FTM0_Ch4_Ch5_IRQn            = 101,              /**< FTM0 Channel 4 and 5 interrupt */
  FTM0_Ch6_Ch7_IRQn            = 102,              /**< FTM0 Channel 6 and 7 interrupt */
  FTM0_Fault_IRQn              = 103,              /**< FTM0 Fault interrupt */
  FTM0_Ovf_Reload_IRQn         = 104,              /**< FTM0 Counter overflow and Reload interrupt */
  FTM1_Ch0_Ch1_IRQn            = 105,              /**< FTM1 Channel 0 and 1 interrupt */
  FTM1_Ch2_Ch3_IRQn            = 106,              /**< FTM1 Channel 2 and 3 interrupt */
  FTM1_Ch4_Ch5_IRQn            = 107,              /**< FTM1 Channel 4 and 5 interrupt */
  FTM1_Ch6_Ch7_IRQn            = 108,              /**< FTM1 Channel 6 and 7 interrupt */
  FTM1_Fault_IRQn              = 109,              /**< FTM1 Fault interrupt */
  FTM1_Ovf_Reload_IRQn         = 110,              /**< FTM1 Counter overflow and Reload interrupt */
  FTM2_Ch0_Ch1_IRQn            = 111,              /**< FTM2 Channel 0 and 1 interrupt */
  FTM2_Ch2_Ch3_IRQn            = 112,              /**< FTM2 Channel 2 and 3 interrupt */
  FTM2_Ch4_Ch5_IRQn            = 113,              /**< FTM2 Channel 4 and 5 interrupt */
  FTM2_Ch6_Ch7_IRQn            = 114,              /**< FTM2 Channel 6 and 7 interrupt */
  FTM2_Fault_IRQn              = 115,              /**< FTM2 Fault interrupt */
  FTM2_Ovf_Reload_IRQn         = 116,              /**< FTM2 Counter overflow and Reload interrupt */
  FTM3_Ch0_Ch1_IRQn            = 117,              /**< FTM3 Channel 0 and 1 interrupt */
  FTM3_Ch2_Ch3_IRQn            = 118,              /**< FTM3 Channel 2 and 3 interrupt */
  FTM3_Ch4_Ch5_IRQn            = 119,              /**< FTM3 Channel 4 and 5 interrupt */
  FTM3_Ch6_Ch7_IRQn            = 120,              /**< FTM3 Channel 6 and 7 interrupt */
  FTM3_Fault_IRQn              = 121,              /**< FTM3 Fault interrupt */
  FTM3_Ovf_Reload_IRQn         = 122,              /**< FTM3 Counter overflow and Reload interrupt */
  FTFM_EEERAM_ECC_ERR_IRQn     = 152,              /**< FFTM EEERAM ECC error */
  FTFM_Mgate_ECC_ERR_IRQn      = 153               /**< FFTM Mgate ECC error */
} IRQn_Type;

/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
   unsigned int ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
   unsigned int RESERVED0[24U];
   unsigned int ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
   unsigned int RESERVED1[24U];
   unsigned int ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
   unsigned int RESERVED2[24U];
   unsigned int ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
   unsigned int RESERVED3[24U];
   unsigned int IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
   unsigned int RESERVED4[56U];
   unsigned short  IP[240U];            /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
   unsigned int RESERVED5[644U];
   unsigned int STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_Type;

typedef struct
{
  volatile const  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  volatile uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  volatile uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  volatile uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  volatile uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  volatile uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  volatile uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  volatile uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  volatile uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  volatile uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  volatile uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  volatile uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  volatile uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  volatile const  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  volatile const  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  volatile const  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  volatile const  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  volatile const  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  volatile uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

/***********************************************************************
 *         Macro Denifition
 ***********************************************************************/
#define __NVIC_PRIO_BITS               4        /**< Number of priority bits implemented in the NVIC */

/* S32_NVIC - Peripheral instance base addresses */
/** Peripheral S32_NVIC base address */
#define NVIC_BASE       0xE000E100UL
/** Peripheral S32_NVIC base pointer */
#define NVIC            ((NVIC_Type *) NVIC_BASE)
#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */
#define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct */
#endif
