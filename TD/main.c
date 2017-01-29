#include <stdint.h>

#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"
#include "globalObjects.h"

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

	test_pixels();

	uart_putchar('s');
	uart_putchar('e');

	for (int i = 0; i < 8; i++){
		for(int j = 0; j < 8;j++){
			frame[8*i+j].r = 255 - 16*(8*i+j);
			frame[8*i+j].g = 0;
			frame[8*i+j].b = 0;
		}
	}

	display_frame();
	//test_pixels();
	return 0;
}
