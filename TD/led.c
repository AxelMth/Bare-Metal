#include "registerManager.h"
#include "led.h"

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
	GPIOD_PDDR |= 1<<5;
	GPIOE_PDDR |= 1<<29;

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
