#include "registerManager.h"
#include "uart.h"

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

	uint8_t mask = GETONEBIT(UART0_S1,7);
	if (!(mask & 0))
		UART0_D = c;

}

unsigned char uart_getchar(){

	unsigned char result;
	uint8_t mask = GETONEBIT(UART0_S1,5);
	if (!(mask & 0))
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
	for(i = 0; i < size; i++){
		*(s+i) = uart_getchar();
	}
	*(s+i) = '\0';

}
