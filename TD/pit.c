#include "pit.h"
#include "registerManager.h"
#include "led.h"
#include "irq.h"
#include "globalObjects.h"

#define PIT_MCR (*(volatile uint32_t *) 0x40037000)
#define PIT_LDVAL0 (*(volatile uint32_t *) 0x40037100)
#define PIT_TFLG0 (*(volatile uint32_t *) 0x4003710C)
#define PIT_TCTRL0 (*(volatile uint32_t *) 0x40037108)
#define SIM_SCGC6 (*(volatile uint32_t *) 0x4004803C)

void pit_init(){
	// Activation de l'horloge du pit
	SETONEBIT(SIM_SCGC6,23);
	// Clock for standard PIT timers is enabled.
	// Timers continue to run in Debug mode.
	PIT_MCR = 0x00;
	// On rentre la valeur du compteur (ici on rafraîchit 70 fois par secondes pour chaque ligne , il faut donc que l'on rafraîchisse 8 fois plus vite)
	PIT_LDVAL0 = 24000000/(70*8);
	// Test clignotement led
	//PIT_LDVAL0 = 24000000;
	// Activation du timer et des interruptions
	PIT_TCTRL0 |= (1<<1) | (1<<0);
	// Activation des interruptions sur le PIT
	irq_enable(22);
}

void PIT_IRQHandler(){
	// On clear le flag d'interruption
	PIT_TFLG0 |= 1;
	// On rafraîchit l'image après l'attente définit plus haut
	display = 1;
	
	// Test led
	//led_r_toggle();
}
