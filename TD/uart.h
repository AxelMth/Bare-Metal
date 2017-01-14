// Définition des registres des horloges
#define SIM_SCGC5 (*(volatile uint32_t *)0x40048038)

// Registre d'activation de l'horloge UART0
#define SIM_SCGC4 (*(volatile uint32_t *) 0x40048034)

// Registre de selection de l'horloge de source et de transmission de UART0
#define SIM_SOPT2 (*(volatile uint32_t *) 0x40048004)

// Registre d'activation de l'UART0 en reception transmission
#define UART0_C2 (*(volatile uint8_t *) 0x4006A003)

// Registre de gestion de l'oversampling
#define UART0_C4 (*(volatile uint8_t *) 0x4006A00A)

// Registre de configuration du SBR et mode 8N1
#define UART0_BDH (*(volatile uint8_t *) 0x4006A000)
#define UART0_BDL (*(volatile uint8_t *) 0x4006A001)
#define UART0_C1 (*(volatile uint8_t *) 0x4006A002)

// Activiation du port A en mode UART
#define PORTA_PCR1 (*(volatile uint32_t *) 0x40049004)
#define PORTA_PCR2 (*(volatile uint32_t *) 0x40049008)

void uart_init(void);
void uart_putchar(char c);
unsigned char uart_getchar();
void uart_puts(const char *s);
void uart_gets(char *s,int size);
