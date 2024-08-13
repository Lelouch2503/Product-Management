#include "nvic.h"
 
void NVIC_EnableInterrupt(const IRQn_Type IRQ_number)
{
	NVIC->ISER[IRQ_number >> 5u] |= (1 << (IRQ_number % 32));  
}

void NVIC_DisableInterrupt(IRQn_Type IRQ_number) {
	NVIC->ICER[IRQ_number >> 5U] |= (1 << (IRQ_number % 32));  
}

void NVIC_ClearPendingFlag(IRQn_Type IRQ_number) {
	 if ((int)(IRQ_number) >= 0)
  {
    NVIC->ICPR[IRQ_number >> 5UL] |= ((1UL << (IRQ_number)) & 0x1FUL);
  }
}

void NVIC_SetPriority(IRQn_Type IRQ_number, unsigned char priority)
{
  if ((int32_t)(IRQ_number) >= 0)
  {
    NVIC->IP[((uint32_t)IRQ_number)]               = (uint8_t)(((uint32_t)priority << (8U - (uint32_t)__NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
  else
  {
    SCB->SHP[(((uint32_t)IRQ_number) & 0xFUL)-4UL] = (uint8_t)(((uint32_t)priority << (8U - (uint32_t)__NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
}
