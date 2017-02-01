#include <stdint.h>

#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"
#include "globalObjects.h"
#include "pit.h"
#include "init_clocks.h"

// Attente active
void wait(){
	for(int i=0; i<100000; i++)
	     asm volatile("nop");
}

int main() {

	// Initialisation des horloges
	init_clocks();
	
	// Initialisation de la vector table
	irq_init();

	// Initialisation uart
	uart_init();

	// Initialisation des LEDs
	led_init();

	// Initialisation de la matrice de LEDs
	matrix_init();

	// Initialisation des boutons
	button_init();

	// Affichage de image.raw
	//while(1)
	//	display_image();

	// Initialisation du compteur
	pit_init();

	while(1){
		display_frame();
	}

	return 0;
}
