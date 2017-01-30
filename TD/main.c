#include <stdint.h>

#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"
#include "globalObjects.h"
#include "pit.h"

// Attente active
void wait(){
	for(int i=0; i<100000; i++)
	     asm volatile("nop");
}

int main() {

	// Initialisation des horloges
	clocks_init();

	// Initialisation uart
	uart_init();

	// Initialisation des LEDs
	led_init();

	// Initialisation de la matrice de LEDs
	matrix_init();

	// Initialisation de la vector table
	irq_init();

	// Initialisation des boutons
	button_init();

	//while(1)
	//	display_image();

	// Afichage du fichier binaire
	//display_frame();
	
	// Initialisation du compteur
	pit_init();

	while(1){
		if(display)
			display_image();
	}
	return 0;
}
