#include "registerManager.h"
#include "irq.h"
#include "led.h"

#define PORTC_PCR3 (*(volatile uint32_t *) 0x4004B00C)
#define GPIOC_PDDR (*(volatile uint32_t *)0x400FF094)

void button_init(){

	// Active l'horloge du port C
	SETONEBIT(SIM_SCGC5,11);
	
	// Pull-up, pull enable, GPIO, interruption on falling edge
	PORTC_PCR3 |= (1<<0) | (1<<1) | (1<<8) | (1<<17) | (1<<19);
	PORTC_PCR3 &= ~(1<<18) & ~(1<<16);
	
	// Mode entrée
	GPIOC_PDDR &= ~(1<<3);
	
	// Active les interruptions sur le port C/D
	irq_enable(31);
}

void LLWU_IRQHandler(){
	// Active le Interrupt Status Flag
	SETONEBIT(PORTC_PCR3,24);
	led_r_toggle();
	//disable_irq();
	//while(1);
}
