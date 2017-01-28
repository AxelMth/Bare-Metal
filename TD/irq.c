#include "irq.h"
#include "registerManager.h"

#define MAKE_DEFAULT_HANDLER(truc_IRQHandler) void __attribute__((weak)) truc_IRQHandler() {disable_irq(); while(1);}
#define NVIC_ISER (*(volatile uint32_t *) 0xE000E100)
#define NVIC_ICER (*(volatile uint32_t *) 0xE000E180)
#define VTOR (*(volatile uint32_t *)  0xE000ED08)

extern char _stack;
void _start(void);

MAKE_DEFAULT_HANDLER(NMI_Handler);
MAKE_DEFAULT_HANDLER(HardFault_Handler);
MAKE_DEFAULT_HANDLER(SVC_Handler);
MAKE_DEFAULT_HANDLER(PendSV_Handler);
MAKE_DEFAULT_HANDLER(SysTick_Handler);

MAKE_DEFAULT_HANDLER(DMA0_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA3_IRQHandler);
MAKE_DEFAULT_HANDLER(FTFA_IRQHandler);
MAKE_DEFAULT_HANDLER(PMC_IRQHandler);
MAKE_DEFAULT_HANDLER(LLWU_IRQHandler);
MAKE_DEFAULT_HANDLER(SPI0_IRQHandler);
MAKE_DEFAULT_HANDLER(SPI1_IRQHandler);
MAKE_DEFAULT_HANDLER(UART0_IRQHandler);
MAKE_DEFAULT_HANDLER(UART1_IRQHandler);
MAKE_DEFAULT_HANDLER(UART2_IRQHandler);
MAKE_DEFAULT_HANDLER(RTC1_IRQHandler);
MAKE_DEFAULT_HANDLER(RTC2_IRQHandler);
MAKE_DEFAULT_HANDLER(PIT_IRQHandler);
MAKE_DEFAULT_HANDLER(ISO_IRQHandler);
MAKE_DEFAULT_HANDLER(PinA_IRQHandler);
MAKE_DEFAULT_HANDLER(PinCD_IRQHandler);

void *vector_table[] = {
    // Stack and Reset Handler
    &_stack,            /* Top of stack */
    _start,             /* Reset handler */

    // ARM internal exceptions
    NMI_Handler,        /* NMI handler */
    HardFault_Handler,  /* Hard Fault handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    SVC_Handler,        /* SVC handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    PendSV_Handler,     /* Pending SVC handler */
    SysTick_Handler,    /* SysTick hanlder */

    // KL46 External interrupts
    DMA0_IRQHandler,         /* DMA0 interrupt */
    DMA1_IRQHandler,         /* DMA1 interrupt */
    DMA2_IRQHandler,         /* DMA2 interrupt */
    DMA3_IRQHandler,	       /* DMA3 interrupt */
    0,			/* Reserved */
    FTFA_IRQHandler,    /* Read collision Handler */
    PMC_IRQHandler,     /* Low-Voltage Handler */
    LLWU_IRQHandler,    /* Low Leakage Wakeup */
    0,			/* Reserved */
    0, 		  /* Reserved */
    SPI0_IRQHandler,	  /* Single interrupt vector */
    SPI1_IRQHandler, 	  /* Single interrupt vector */
    UART0_IRQHandler,	  /* UART0 Handler */
    UART1_IRQHandler,	  /* UART1 Handler */
    UART2_IRQHandler,	  /* UART2 Handler */
    0,			/* Reserved */
    0, 			/* Reserved */
    0,			/* Reserved */
    0, 			/* Reserved */
    0, 			/* Reserved */
    RTC1_IRQHandler,	  /* Alarm interrupt handler */
    RTC2_IRQHandler, 	  /* Seconds interrupt handler */
    PIT_IRQHandler, 	  /* Single interrupt vector for all channels*/
    ISO_IRQHandler, 	  /* Single interrupt vector for all sources */
    0,			/* Reserved */
    0,			/* Reserved */
    0,			/* Reserved */
    0,			/* Reserved */
    0,			/* Reserved */
    0,			/* Reserved */
    PinA_IRQHandler, 	  /* Pin detect (port A) handler */
    PinCD_IRQHandler,	  /* Pin detect (port C/D) handler */
};

void irq_init(){
   VTOR = (uint32_t) &vector_table;
   enable_irq();
}

void irq_enable(int irq_number){
  SETONEBIT(NVIC_ISER,irq_number);
}

void irq_disable(int irq_number){
  SETONEBIT(NVIC_ICER,irq_number);
}
