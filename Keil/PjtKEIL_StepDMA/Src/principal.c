

#include "DriverJeuLaser.h"

extern long DFT_ModuleAuCarre(short *,int);
extern short LeSignal;
int mod;
int tableau[64];
short int dma_buf[64];

void fct_DFT(void){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for (int i = 0; i<64; i++) {
		tableau[i] = DFT_ModuleAuCarre(dma_buf,i);
	}
}

void init_timer_5ms(void) {
	// Timer 5ms
	Systick_Period_ff(360000);
	Systick_Prio_IT((char) 1, fct_DFT);
	SysTick_On;
	SysTick_Enable_IT ;
}

void init_timer_ADC(void) {
	// Timer 320kHz
	Init_TimingADC_ActiveADC_ff(ADC1, 72);
	Single_Channel_ADC(ADC1, 2);
	Init_Conversion_On_Trig_Timer_ff(ADC1, TIM2_CC2, 225);
	Init_ADC1_DMA1(0, dma_buf);
}

int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();
	init_timer_5ms();
	init_timer_ADC();
	
	

//============================================================================	
	
	
while	(1)
	{
	}
}

