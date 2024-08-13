#include "LPUART.h"

static IRQn_Type get_irqn(LPUART_irq lpuart) {
    switch (lpuart) {
        case LPuart_irq0: return LPUART0_RxTx_IRQn;
        case LPuart_irq1: return LPUART1_RxTx_IRQn;
        case LPuart_irq2: return LPUART2_RxTx_IRQn;
    }
}

uint32_t get_clock_frequency(Clock_Source clk_src) {
    switch (clk_src) {
        case CLOCK_SOSC:
            return SOSC_CLK_FREQ;
        case CLOCK_SIRC:
            return SIRC_CLK_FREQ;
        case CLOCK_FIRC:
            return FIRC_CLK_FREQ;
        case CLOCK_SPLL:
            return SPLL_CLK_FREQ;
    }
}

void LPUART_init(LPUART_Type *base,  uint32_t baud_rate, Clock_Source clk_src) {
		uint8_t lpuart = 0;
		LPUART_irq LPUART_irq = LPuart_irq0;
    // Enable clock for selected LPUART
		if(base == LPUART0)
		{	
			lpuart = PCC_LPUART0_INDEX;
			LPUART_irq = LPuart_irq0;
		}
		else if(base == LPUART1)
		{	
			lpuart = PCC_LPUART1_INDEX;
			LPUART_irq = LPuart_irq1;
		}
		else if(base == LPUART2)
		{	
			lpuart = PCC_LPUART2_INDEX;
			LPUART_irq = LPuart_irq2;
		}
    // Select clock source
    switch (clk_src) {
        case CLOCK_SOSC:
            PCC->PCCn[lpuart] |= PCC_PCCn_PCS(1) | ENABLE_PCC; // SOSC clock
            break;
        case CLOCK_SIRC:
            PCC->PCCn[lpuart] |= PCC_PCCn_PCS(2)| ENABLE_PCC; // SIRC clock
            break;
				case CLOCK_FIRC:
            PCC->PCCn[lpuart] |= PCC_PCCn_PCS(3)| ENABLE_PCC; // FIRC clock
            break;
        case CLOCK_SPLL:
            PCC->PCCn[lpuart] |= PCC_PCCn_PCS(6)| ENABLE_PCC; // SPLL clock
            break;
    }
		base->CTRL = 0;
		// Get the clock frequency
    uint32_t clock = get_clock_frequency(clk_src);
    // Configure LPUART for 8-bit mode, no parity
    base->BAUD |= (LPUART_BAUD_SBR(clock / (16 * baud_rate)) | (15 << 24));

    base->CTRL |= LPUART_CTRL_RE_MASK | LPUART_CTRL_TE_MASK; // Enable receiver and transmitter
    base->CTRL |= LPUART_CTRL_RIE_MASK; // Enable receiver interrupt

    // Enable LPUART interrupt in NVIC
    NVIC_EnableInterrupt(get_irqn(LPUART_irq));
		NVIC_SetPriority(get_irqn(LPUART_irq), 5);
}

void LPUARTx_SendByte(LPUART_Type *LPUARTx, uint8_t data) {
    while (!(LPUARTx->STAT & LPUART_STAT_TDRE_MASK));
    LPUARTx->DATA = data;
}

void LPUARTx_SendString(LPUART_Type *LPUARTx, char *data) {
	while (*data != NULL){
		LPUARTx_SendByte(LPUARTx, *data++);
	}
}

uint8_t LPUARTx_ReadByte(LPUART_Type *LPUARTx) {
    while ((LPUARTx->STAT & LPUART_STAT_RDRF_MASK) >> 21u == 0);
		uint8_t data = (uint8_t)LPUARTx->DATA;
    return data;
}

void LPUART0_RxTx_IRQHandler(void) {
	if (LPUART0->STAT & LPUART_STAT_RDRF_MASK) {


			// Clear interrupt flag
			LPUART0->STAT |= LPUART_STAT_RDRF_MASK;
	}
}


