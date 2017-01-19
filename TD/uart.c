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

// Lecture écriture et registre de contrôle
#define UART0_D (*(volatile uint8_t *) 0x4006A007)
#define UART0_S1 (*(volatile uint8_t *) 0x4006A004)

// Processus d'Initialisation de l'UART0
void uart_init(){

	// Sélection des horloges MCGPLLCLK et MCGPLLCLK/2 pour la sortie UART0
	SIM_SOPT2 = 0x04000000;
	SIM_SOPT2 |= 1<<16;

	// Activation de l'horloge de UART0
	SETONEBIT(SIM_SCGC4,10);

	// Désactivation de la reception et de l'emission de l'UART0
	UART0_C2 = 0;

	// MaJ de l'oversampling maximale avec erreur de moins de 3%
	UART0_C4 = 0x1D;

	// Définition du SBR
	UART0_BDL = 7;

	// SBR + 1 bit de stop
	UART0_BDH = 0;

	// Mode 8N1

	// Pas de parité
	UART0_C1 = 0x12;

	// Activation du port A en mode UART
	PORTA_PCR1 = 0x2 << 8;
	PORTA_PCR2 = 0x2 << 8;

	// Activation des horloges du port A
	SETONEBIT(SIM_SCGC5,9);

	// Activation de la reception et de l'emission de l'UART0
	UART0_C2 = 12;
}

void uart_putchar(char c){

	// Tant que UART0_D n'est pas vide
	while (!(UART0_S1 & 0x80) || !(UART0_S1 & 0x40));
	UART0_D = c;
}

unsigned char uart_getchar(){

start:
			// Tant que le buffer n'est pas prêt
			while (!(UART0_S1 & 0x20));

			// Test Overrun & Framing Error
			if (UART0_S1 & 0x0A) {
				UART0_S1 |= 0x0A;
				goto start;
			}

			return (unsigned char) UART0_D;
}

void uart_puts(const char *s){

	int i=0;
	while(*(s+i) != '\0'){
		uart_putchar(*(s+i));
		i++;
	}
	uart_putchar('\r');
	uart_putchar('\n');
}

void uart_gets(char *s, int size){

	char c;
	int i;
	for(i = 0; i < size; i++){
		c = uart_getchar();
		*(s+i) = c;
	}
	*(s+i) = '\0';

}
