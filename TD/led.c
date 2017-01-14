#include "registerManager.h"
#include "led.h"

void led_init() {

	 // Activation des horloges des ports D et E
	SETONEBIT(SIM_SCGC5,12);
	SETONEBIT(SIM_SCGC5,13);

	// Configuration de la broche PTD5 en GPIO
	CLEARONEBIT(PORTD_PCR5,8);
	SETONEBIT(PORTD_PCR5,9);
	SETONEBIT(PORTD_PCR5,10);

	// Configuration de la broche PTE29 en GPIO
	CLEARONEBIT(PORTE_PCR29,8);
	SETONEBIT(PORTE_PCR29,9);
	SETONEBIT(PORTE_PCR29,10);

	// Configuration des LEDs en sortie
	SETONEBIT(GPIOD_PDDR,5);
	SETONEBIT(GPIOE_PDDR,29);

	// Allumage des deux LEDS
	led_g_on();
	led_r_on();
}


// LED verte
void led_g_on() {
	GPIOD_PCOR = 0xffffffff;
}

void led_g_off() {
	GPIOD_PSOR = 0xffffffff;
}

void led_g_toggle() {
	GPIOD_PTOR = 0xffffffff;
}


// LED rouge
void led_r_on() {
	GPIOE_PCOR = 0xffffffff;
}

void led_r_off() {
	GPIOE_PSOR = 0xffffffff;
}

void led_r_toggle() {
	GPIOE_PTOR = 0xffffffff;
}
