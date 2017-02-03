.thumb
.global _start
.type _start,%function
_start:
      	ldr r0,=_stack
     	mov sp, r0
      	bl init_bss
	bl copy_rom_ram
	bl main
_exit:
      	b _exit
