#include "led.h"
#include "clocks.h"

// Attente active
void wait(){
	for(int i=0; i<100000; i++)
	     asm volatile("nop");
}

int main() {

	// Initialisation des horloges
	clocks_init();

	// Initialisation des LEDs
	led_init();

	while (1) {
		led_r_toggle();
		led_g_toggle();
		wait();
	}

	return 0;

}
