#include "led.h"
#include "clocks.h"
#include "uart.h"

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

	uart_putchar('b');
	uart_putchar('o');
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
	uart_puts(s);

	
	//char * test;
	//uart_gets(test,);
	
	// Initialisation des LEDs
	/*led_init();

	while (1) {
		led_r_toggle();
		led_g_toggle();
		wait();
	}*/

	return 0;
}
