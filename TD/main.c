#include <stdint.h>

#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"

volatile uint32_t sum;
volatile int i;
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

	matrix_init();

	return 0;

	// Test fonctions uart_*();

	/*uart_putchar('o');
	uart_putchar('n');
	uart_putchar('j');
	uart_putchar('o');
	uart_putchar('u');
	uart_putchar('r');
	uart_putchar(' ');
	uart_putchar('!');
	unsigned char c = uart_getchar();
	uart_putchar(c);
	uart_puts("Salut");
	char * s = "";
	uart_gets(s,5);
	uart_puts(s);*/

	// Somme des octets aléatoires
	/*for (i = 0; i < 1000; i++){
		sum += uart_getchar();
	}

	// Clignotement de la led rouge accusant la reception des 1000 octets
	led_r_toggle();

	// Boucle infinie permettant de regarder l'état des reigstres
	while(1);
*/

}
