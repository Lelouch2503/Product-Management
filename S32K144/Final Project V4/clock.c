#include "clock.h"

void SOSC_Init(void)
{
	SOSCDIV |= 0x00000101; /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
	SOSCCFG |= 0x00000024; /* Range=2: Medium freq (SOSC betw 1MHz-8MHz)*/
													 /* HGO=0: Config xtal osc for low power */
													 /* EREFS=1: Input is external XTAL */
	while(SOSCCSR & (1 << 23)); /* Ensure SOSCCSR unlocked */
	SOSCCSR =0x00000001; /* LK=0:          SOSCCSR can be written */
													 /* SOSCCMRE=0:    OSC CLK monitor IRQ if enabled */
													 /* SOSCCM=0:      OSC CLK monitor disabled */
													 /* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
													 /* SOSCLPEN=0:    Sys OSC disabled in VLP modes */
													 /* SOSCSTEN=0:    Sys OSC disabled in Stop modes */
													 /* SOSCEN=1:      Enable oscillator */
	while(!(SOSCCSR & (1 << 24))); /* Wait for sys OSC clk valid */
}

void SPLL_160Mhz_init(void)
{
	while(SPLLCSR & (1 << 23)); /* Ensure SPLLCSR unlocked */
	SPLLCSR |= 0x00000000; /* SPLLEN=0: SPLL is disabled (default) */
	SPLLDIV |= 0x00000302; /* SPLLDIV1 divide by 2; SPLLDIV2 divide by 4 */
	SPLLCFG |= 0x00180000; /* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
														 /* MULT=24:  Multiply sys pll by 4*24=40 */
														 /* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz */
	while(SPLLCSR & (1 << 23)); /* Ensure SPLLCSR unlocked */
	SPLLCSR |= 0x00000001; /* LK=0:          SPLLCSR can be written */
														 /* SPLLCMRE=0:    SPLL CLK monitor IRQ if enabled */
														 /* SPLLCM=0:      SPLL CLK monitor disabled */
														 /* SPLLSTEN=0:    SPLL disabled in Stop modes */
														 /* SPLLEN=1:      Enable SPLL */
	while(!(SPLLCSR & (1 << 24))); /* Wait for SPLL valid */
}

void NormalRUNmode_80MHz(void) 
{

	SCGRCCR = ((6<<24) /* PLL as clock source*/
							| (1 << 16)  /* DIVCORE=1, div. by 2: Core clock = 160/2 MHz = 80 MHz*/
							| (1 << 4)    /* DIVBUS=1, div. by 2: bus clock = 40 MHz*/
							| (2 << 0));  /* DIVSLOW=2, div. by 2: SCG slow, flash clock= 26 2/3 MHz*/
	while (((SCGCSR & 0xF000000) >> 24) != 6) {}
	/* Wait for sys cik src = SPLL */
}
