#include <stdint.h>
#include "led.h"
#include "init_clocks.h"

#define MCG_C1 (*(volatile uint8_t *) 0x40064000)
#define MCG_C2 (*(volatile uint8_t *) 0x40064001)
#define MCG_C5 (*(volatile uint8_t *) 0x40064004)
#define MCG_C6 (*(volatile uint8_t *) 0x40064005)

#define MCG_S  (*(volatile uint8_t *) 0x40064006)

#define SIM_COPC  (*(volatile uint32_t *) 0x40048100)

void init_clocks(){

  	// Desactivation du COP Watchdog Timeout
  	SIM_COPC &= (0 << 2) & (0 << 3);

	// Selects the range of frequency for quartz oscillator
	MCG_C2 = 0x2C;

	// Selects an external reference clock as clock source and set 256 as divide factor
	MCG_C1 = 0x98;

	int i;
	// Waits for OSCINIT0's initialization
	for (i = 0 ; i < 20000 ; i++)
	{
		// Jump out early if OSCINIT sets before loop finishes
		if (MCG_S & (1<<1)) break;
	}

	// Wait for Reference clock Status bit to clear
	for (i = 0 ; i < 2000 ; i++)
	{
		// Jump out early if IREFST clears before loop finishes
		if (!(MCG_S & 0x10)) break;
	}

	// Wait for clock status bits to show clock source is ext ref clk
	for (i = 0 ; i < 2000 ; i++)
	{
		// Jump out early if CLKST shows EXT CLK selected before loop finishes
		if (MCG_S & 8) break;
	}
	// Now in FBE
	// Configures MCG_C5 to set the PLL reference clock at the right frequency
	MCG_C5 = 3;

	// Selects the pll sets the PLL multiplier
	MCG_C6 = (1<<6);

	// Wait for PLLST status bit to set
	for (i = 0 ; i < 2000 ; i++)
	{
		// Jump out early if PLLST sets before loop finishes
		if (MCG_S & (1<<5)) break;
	}

	// Wait for LOCK bit to set
	for (i = 0 ; i < 4000 ; i++)
	{
		// Jump out early if LOCK sets before loop finishes
		if (MCG_S & (1<<6)) break;
	}

	// Now in PBE

	// Selects PLL and set 256 as divide factor
	MCG_C1 = 0x18;

	// Wait for clock status bits to update
	for (i = 0 ; i < 2000 ; i++)
	{
	 	// Jump out early if CLKST = 3 before loop finishes
	 	if (MCG_S & (3<<2)) break;
	}

	// Now in PEE
}
