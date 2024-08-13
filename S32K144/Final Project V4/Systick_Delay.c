#include "Systick_Delay.h"

void DelayMillis(void)
{
	S32_SysTick->RVR |= 80000-1;
	S32_SysTick->CVR = 0;
	while((S32_SysTick->CSR & 0x00010000) == 0); // Wait for bit 16(counter flag to set)
}

void delay_ms(unsigned long t)
{
	for(;t>0;t--)
		{
			DelayMillis();
		}
}

void initSysTick(void) {		
	S32_SysTick->CSR = 0;
	S32_SysTick->RVR |= (CLK_CORE / 1000u);
	S32_SysTick->CVR = 0;
	S32_SysTick->CSR |= (5<<0);
}
