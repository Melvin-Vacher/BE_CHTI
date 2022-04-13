

#include "DriverJeuLaser.h"

void CallBackSon(void);

int FinSon;

void StartSon(void) {
	FinSon = 0;
}

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();
Active_IT_Debordement_Timer(TIM4, 2, CallBackSon);
Timer_1234_Init_ff(TIM4, (unsigned int) 6552);
	
StartSon();

PWM_Init_ff(TIM3,3, (unsigned int) 720);
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);

	
	

//============================================================================	
	
	
while	(1)
	{
	}
}

