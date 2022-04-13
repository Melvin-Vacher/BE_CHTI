

#include "DriverJeuLaser.h"

extern long DFT_ModuleAuCarre(short *,int);
extern short LeSignal;
int mod;
int tableau[64];

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

for (int i = 0; i<64; i++) {
	tableau[i] = DFT_ModuleAuCarre(&LeSignal,i);
}
	
	

//============================================================================	
	
	
while	(1)
	{
	}
}

