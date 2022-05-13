#include "DriverJeuLaser.h"
#include "Affichage_Valise.h"
#define NB_JOUEURS 6
#define MAX_CPT_CIBLE 300 //Changement de cible toutes les 1.5 secondes
#define SEUIL 100

//61624

extern long DFT_ModuleAuCarre(short *,int);
extern short LeSignal;
int FinSon;
short int dma_buf[64];
int compteur_changement_cible;

int scores[NB_JOUEURS]; // Table des scores des joueurs
char cible_touchee_par_joueur[NB_JOUEURS]; // Sert à savoir si un joueur a déjà touché la cible depuis le dernier changement de cible
int puissance_par_joueur[NB_JOUEURS]; // Sert à récupérer les valeurs de la DFT
char num_cible; // Numéro de la cible active (allant de 0 à 3)

void fct_DFT(void);

// Les joueurs sont numérotés de 0 à 5

// Initialisation des scores des joueurs
void init_scores() {
	for (int i; i<NB_JOUEURS; i++) {
		scores[i] = 0;
	}
}

// Retourne la fréquence normalisée en fonction du numéro du joueur
int freq_norm(int nb_joueur) {
	switch (nb_joueur) {
		case 0:
			return 17; // 85 kHz
		case 1:
			return 18; // 90 kHz
		case 2:
			return 19; // 95 kHz
		case 3:
			return 20; // 100 kHz
		case 4:
			return 23; // 115 kHz
		case 5:
			return 24; // 120 kHz
		default:
			return 0;
	}
}

void clear_LED_cibles(void) {
	Prepare_Clear_LED(LED_Cible_1);
	Prepare_Clear_LED(LED_Cible_2);
	Prepare_Clear_LED(LED_Cible_3);
	Prepare_Clear_LED(LED_Cible_4);
	Mise_A_Jour_Afficheurs_LED();
}

void cible_suivante() {
	//num_cible = (num_cible + 1) % 4;
	char alea_cible = (dma_buf[0] + dma_buf[1]) % 4;
	if (alea_cible != num_cible) { //On veut changer de cible à chaque fois
		num_cible = alea_cible;
	} else {
		num_cible = (alea_cible + 1) % 4;
	}
	
	Choix_Capteur(num_cible + 1);
	clear_LED_cibles();
	switch (num_cible) {
		case 0:
			Prepare_Set_LED(LED_Cible_1);
			break;
		case 1:
			Prepare_Set_LED(LED_Cible_2);
			break;
		case 2:
			Prepare_Set_LED(LED_Cible_3);
			break;
		default:
			Prepare_Set_LED(LED_Cible_4);
	}
	Mise_A_Jour_Afficheurs_LED();
	for (int i = 0; i<NB_JOUEURS; i++) {
		cible_touchee_par_joueur[i] = 0;
	}
}

void init_timer_5ms(void) {
	// Timer 5ms
	Systick_Period_ff(360000);
	Systick_Prio_IT((char) 9, fct_DFT);
	SysTick_On;
	SysTick_Enable_IT ;
}

void init_timer_ADC(void) {
	// Timer 320kHz
	Init_TimingADC_ActiveADC_ff(ADC1, 72);
	Single_Channel_ADC(ADC1, 2); // Signal d'entrée sur PA2
	Init_Conversion_On_Trig_Timer_ff(ADC1, TIM2_CC2, 225);
	Init_ADC1_DMA1(0, dma_buf);
}

void CallBackSon(void);

void init_son(void) {
	FinSon = 1;
	Active_IT_Debordement_Timer(TIM4, 2, CallBackSon);
	Timer_1234_Init_ff(TIM4, (unsigned int) 6552);

	PWM_Init_ff(TIM3,3, (unsigned int) 720);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
}

void StartSon(void) {
	FinSon = 0;
}

void fct_DFT(void) {
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	// int puissance_moyenne = DFT_ModuleAuCarre(dma_buf,0); // Calcul de la puissance moyenne
	for (int i = 0; i<NB_JOUEURS; i++) {
		puissance_par_joueur[i] = DFT_ModuleAuCarre(dma_buf,freq_norm(i)); // Calcul de la DFT pour le joueur i
		if ((puissance_par_joueur[i] > SEUIL) && !(cible_touchee_par_joueur[i])) {
			cible_touchee_par_joueur[i] = 1; // On enregistre le tir du joueur i
			scores[i]++; // Le joueur i gagne un point
			Prepare_Afficheur(i+1, scores[i]);
			Mise_A_Jour_Afficheurs_LED();
			StartSon(); // Déclencher le son
		}
	}
	compteur_changement_cible++;
	if (compteur_changement_cible == MAX_CPT_CIBLE) {
		compteur_changement_cible = 0;
		cible_suivante();
	}
}

int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	num_cible = 3; //Dernière cible
	compteur_changement_cible = 0;
	
	Init_Affichage();
	Choix_Capteur(0);
	CLOCK_Configure();
	init_timer_5ms();
	init_timer_ADC();
	init_son();
	init_scores();
	cible_suivante(); //Première cible

//============================================================================	
	
	
while	(1)
	{
	}
}

