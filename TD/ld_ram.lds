ENTRY(_start)

MEMORY
	{
		flash (rx) : ORIGIN = 0x00000800, LENGTH = 254k
		flash_config (rx) : ORIGIN = 0x00000400, LENGTH = 32
		raml (!rx) : ORIGIN = 0x1fffe000, LENGTH = 8k
		ramh (!rx) : ORIGIN = 0x20000000, LENGTH = 24k
	}

stack_size = 8;
_stack = ORIGIN(raml)+LENGTH(raml);
_stack_end = _stack - stack_size;

SECTIONS {
	 .text : {
		 *(.text)
		 _etext = . ;
	 } > ramh
	 .data : {
		  _data = . ;
		  *(.data)
		  _edata = . ;
	 } > ramh
	 .bss : {
		   _bstart = . ;
		   *(.bss) *(COMMON)
		   _bend = . ;
	 } > ramh
	.flash_config :	{
		   *(.flash_config)
	} > flash_config
	.rodata : {
			 *(.rodata)
	 } > flash
}
