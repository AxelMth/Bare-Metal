#include <stdint.h>

extern char _etext, _btext, _data,
 _edata, _bstart, _bend, _ecopy;

// ROM has placed .data at end of .text.
// Copy .data to RAM
void copy_rom_ram(){
	char *dst = &_edata;
	char *src = &_btext;
	while (dst < &_ecopy && src < &_etext)
		*dst++ = *src++;
}

//Initialisation du bss
void init_bss(){
	char *dst;
	for (dst = &_bstart; dst < &_bend; dst++)
		 *dst = 0;
}
