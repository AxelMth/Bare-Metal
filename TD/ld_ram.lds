ENTRY(_start)

MEMORY
	{
		flash (rx) : ORIGIN = 0x00000000, LENGTH = 254k
		flash_config (rx) : ORIGIN = 0x00000400, LENGTH = 32
		raml (!rx) : ORIGIN = 0x1fffe000, LENGTH = 8k
		ramh (!rx) : ORIGIN = 0x20000000, LENGTH = 24k
	}

stack_size = 8;
_stack = ORIGIN(raml)+LENGTH(raml);
_stack_end = _stack - stack_size;

SECTIONS {

	 .vector_t : {
	 	*(vector_t)
	 } > flash

	 .flash_config : {
		   *(.flash_config)
	 } > flash_config

	 .text 0x1000 : {
		 _btext = .;
		 *(.text)
		 _etext = .;
	 } > flash
	
	 .data : {
		 _data = . ;
		 *(.data)
		 _edata = . ;
	 } > flash 

	 .rodata : {
		 *(.rodata)
	 } > flash

	.text_ram : {
		_btext_ram = .;
		. += SIZEOF(.text)+SIZEOF(.data); 
		_etext_ram = .;
	} > ramh
	
	.bss : {
		 _bstart = . ;
		 *(.bss) *(COMMON)
		 _bend = . ;
	 } > ramh
}
