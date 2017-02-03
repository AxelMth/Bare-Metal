extern char _etext, _btext, _data,
 _edata, _bstart, _bend, _btext_ram, _etext_ram;

// ROM has placed .data at end of .text.
// Copy .data to RAM
void copy_rom_ram(){
	char *dst = &_btext_ram;
	char *src = &_btext;
	while (dst < &_etext_ram && src < &_data)
		*dst++ = *src++;
}

//Initialisation du bss
void init_bss(){
	char *dst;
	for (dst = &_bstart; dst < &_bend; dst++)
		 *dst = 0;
}
