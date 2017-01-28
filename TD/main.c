#include <stdint.h>

#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"

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

	//while(1)
	//	display_image();
	
	// Initialisation des boutons
	button_init();
	
	return 0;
}
