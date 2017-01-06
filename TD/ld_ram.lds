ENTRY(main)

MEMORY 
	{
		rom (rx) : ORIGIN = 0, LENGTH = 256k
		raml (!rx) : ORIGIN = 0x1fffe000, LENGTH = 8k
		ramh (!rx) : ORIGIN = 0x20000000, LENGTH = 24k
	}

stack_size = 8;
_stack_start = ORIGIN(raml)+LENGTH(raml);
_stack_end = _stack_start - stack_size;
   
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
}
