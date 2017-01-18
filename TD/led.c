#include "registerManager.h"
#include "led.h"

// Définition des registres de configuration des broches en GPIO
#define PORTD_PCR5 (*(volatile uint32_t *)0x4004C014)
#define PORTE_PCR29 (*(volatile uint32_t *)0x4004D074)

// Définition des registres de configuration des broches en sortie
#define GPIOD_PDDR (*(volatile uint32_t *)0x400FF0D4)
#define GPIOE_PDDR (*(volatile uint32_t *)0x400FF114)

// Définition des registres d'allumage des LEDs
#define GPIOD_PCOR (*(volatile uint32_t *)0x400FF0C8)
#define GPIOE_PCOR (*(volatile uint32_t *)0x400FF108)

// Définition des registres d'exctinction des LEDs
#define GPIOD_PSOR (*(volatile uint32_t *)0x400FF0C4)
#define GPIOE_PSOR (*(volatile uint32_t *)0x400FF104)

// Définition des registres de toggle des LEDs
#define GPIOD_PTOR (*(volatile uint32_t *)0x400FF0CC)
#define GPIOE_PTOR (*(volatile uint32_t *)0x400FF10C)

void led_init() {

	 // Activation des horloges des ports D et E
	//SETONEBIT(SIM_SCGC5,12);
	//SETONEBIT(SIM_SCGC5,13);
	SIM_SCGC5 |= ((1<<12) | (1<<13));

	// Configuration de la broche PTD5 en GPIO
	PORTD_PCR5 |= 1<<8;

	// Configuration de la broche PTE29 en GPIO
	PORTE_PCR29 |= 1<<8;

	// Configuration des LEDs en sortie
	SETONEBIT(GPIOD_PDDR,5);
	SETONEBIT(GPIOE_PDDR,29);

	// Allumage des deux LEDS
	led_g_on();
	led_r_on();
}


// LED verte
void led_g_on() {
	SETONEBIT(GPIOD_PCOR,5);
}

void led_g_off() {
	SETONEBIT(GPIOD_PSOR,5);
}

void led_g_toggle() {
	SETONEBIT(GPIOD_PTOR,5);
}


// LED rouge
void led_r_on() {
	SETONEBIT(GPIOE_PCOR,29);
}

void led_r_off() {
	SETONEBIT(GPIOE_PSOR,29);
}

void led_r_toggle() {
	SETONEBIT(GPIOE_PTOR,29);
}
