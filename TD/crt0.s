.thumb
.global _start
_start:
      	ldr r0,=_stack
     	mov sp, r0
      	bl init_bss
	bl main
_exit:
      	b _exit
