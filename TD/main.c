#include <stdint.h>

#include "led.h"
#include "clocks.h"
#include "uart.h"

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

	/*uart_putchar('b');
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
	uart_puts(s);*/

	for (i = 0; i < 1000; i++){
		sum += uart_getchar();
	}
	led_r_toggle();
	while(1);

	// Initialisation des LEDs
	/*led_init();//wait();

	led_r_toggle();//wait();
	led_g_toggle();//wait();
		
	led_r_on(); //wait();
	led_g_on();//wait();

	led_r_off();//wait();
	led_g_off();//wait();*/

	return 0;
}
