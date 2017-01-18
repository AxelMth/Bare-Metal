#include "registerManager.h"
#include "uart.h"

// Registre d'activation de l'horloge UART0
#define SIM_SCGC4 (*(volatile uint32_t *) 0x40048034)

// Registre de selection de l'horloge de source et de transmission de UART0
#define SIM_SOPT2 (*(volatile uint32_t *) 0x40048004)

// Registre d'activation de l'UART0 en reception transmission
#define UART0_C2 (*(volatile uint8_t *) 0x4006A003)

// Registre de gestion de l'oversampling
#define UART0_C4 (*(volatile uint8_t *) 0x4006A00A)

// Registre de configuration du SBR et mode 8N1
#define UART0_BDH (*(volatile uint8_t *) 0x4006A000)
#define UART0_BDL (*(volatile uint8_t *) 0x4006A001)
#define UART0_C1 (*(volatile uint8_t *) 0x4006A002)

// Activiation du port A en mode UART
#define PORTA_PCR1 (*(volatile uint32_t *) 0x40049004)
#define PORTA_PCR2 (*(volatile uint32_t *) 0x40049008)

// Lecture écriture
#define UART0_D (*(volatile uint8_t *) 0x4006A007)
#define UART0_S1 (*(volatile uint8_t *) 0x4006A008)

void uart_init(){

	// Activation de l'horloge de UART0
	SETONEBIT(SIM_SCGC4,10);

	// Désactivation de la reception et de l'emission de l'UART0
	CLEARONEBIT(UART0_C2,2);
	CLEARONEBIT(UART0_C2,3);

	// Sélection des horloges MCGPLLCLK et MCGPLLCLK/2 pour la sortie UART0
	CLEARONEBIT(SIM_SOPT2,27);
	SETONEBIT(SIM_SOPT2,26);

	// Séléction de MCGPLLCLK/2
	SETONEBIT(SIM_SOPT2,16);

	// MaJ de l'oversampling maximale avec erreur de moins de 3%
	SETONEBIT(UART0_C4,0);
	CLEARONEBIT(UART0_C4,1);
	SETONEBIT(UART0_C4,2);
	SETONEBIT(UART0_C4,3);
	SETONEBIT(UART0_C4,4);

	SETONEBIT(UART0_C4,5); // 10-bits

	// Définition du SBR
	UART0_BDL = 0x07;

	// SBR + 1 bit de stop
	for (int i = 0; i < 6; i++)
		CLEARONEBIT(UART0_BDH,i);

	// Mode 8N1

	// Pas de parité
	CLEARONEBIT(UART0_C1,1);
	// 8 bits de data
	CLEARONEBIT(UART0_C1,4);


	// Activation du port A en mode UART
	CLEARONEBIT(PORTA_PCR1,8);
	SETONEBIT(PORTA_PCR1,9);
	CLEARONEBIT(PORTA_PCR1,10);

	CLEARONEBIT(PORTA_PCR2,8);
	SETONEBIT(PORTA_PCR2,9);
	CLEARONEBIT(PORTA_PCR2,10);

	// Activation des horloges du port A
	SETONEBIT(SIM_SCGC5,9);

	// Activation de la reception et de l'emission de l'UART0
	SETONEBIT(UART0_C2,2);
	SETONEBIT(UART0_C2,3);
}


void uart_putchar(char c){

	while (UART0_S1 & (1<<7))
		UART0_D = c;

}

unsigned char uart_getchar(){

	unsigned char result = 'c';
	while (UART0_S1 & (1<<5))
		result = UART0_D;

	return result;

}

void uart_puts(const char *s){

	int i=0;
	while(*(s+i) != '\0'){
		uart_putchar(*(s+i));
		i++;
	}
	uart_putchar('\n');

}

void uart_gets(char *s, int size){

	int i;
	for(i = 0; i < size; i++)
		*(s+i) = uart_getchar();
	*(s+i) = '\0';

}
