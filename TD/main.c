#include <stdint.h>

#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"

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
	//led_init();

	// Initialisation de la matrice de LEDs
	matrix_init();

	// Test de pixels (1s dégradé de rouge par ligne puis 1s dégradé de vert par ligne etc...)
	//test_pixels();
	while(1)
		display_image();

	return 0;

}
