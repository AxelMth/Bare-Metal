#include "registerManager.h"

// Définition des registres de configuration des broches en GPIO

// Port A
#define PORTA_PCR4 (*(volatile uint32_t *)0x40049010)
#define PORTA_PCR12 (*(volatile uint32_t *)0x40049030)
#define PORTA_PCR13 (*(volatile uint32_t *)0x40049034)

// Port B
#define PORTB_PCR0 (*(volatile uint32_t *)0x4004A000)
#define PORTB_PCR1 (*(volatile uint32_t *)0x4004A004)
#define PORTB_PCR2 (*(volatile uint32_t *)0x4004A008)

// Port C
#define PORTC_PCR8 (*(volatile uint32_t *)0x4004B020)
#define PORTC_PCR9 (*(volatile uint32_t *)0x4004B024)

// Port D
#define PORTD_PCR2 (*(volatile uint32_t *)0x4004C008)
#define PORTD_PCR4 (*(volatile uint32_t *)0x4004C010)
#define PORTD_PCR5 (*(volatile uint32_t *)0x4004D014)
#define PORTD_PCR6 (*(volatile uint32_t *)0x4004C018)
#define PORTD_PCR7 (*(volatile uint32_t *)0x4004C01C)

// Définition des registres de configuration des broches en sortie
#define GPIOA_PDDR (*(volatile uint32_t *)0x400FF014)
#define GPIOB_PDDR (*(volatile uint32_t *)0x400FF054)
#define GPIOC_PDDR (*(volatile uint32_t *)0x400FF094)
#define GPIOD_PDDR (*(volatile uint32_t *)0x400FF0D4)

// Définition des registres de configuration des broches en sortie
#define GPIOA_PSOR (*(volatile uint32_t *)0x400FF004)
#define GPIOB_PSOR (*(volatile uint32_t *)0x400FF044)
#define GPIOC_PSOR (*(volatile uint32_t *)0x400FF084)
#define GPIOD_PSOR (*(volatile uint32_t *)0x400FF0C4)

// Définition des registres de configuration des broches en sortie
#define GPIOA_PCOR (*(volatile uint32_t *)0x400FF008)
#define GPIOB_PCOR (*(volatile uint32_t *)0x400FF048)
#define GPIOC_PCOR (*(volatile uint32_t *)0x400FF088)
#define GPIOD_PCOR (*(volatile uint32_t *)0x400FF0C8)

// Définition des fonctions d'initialisation des broches du driver
static inline void RST(int x) {if(!x) {SETONEBIT(GPIOB_PCOR,2);} else {SETONEBIT(GPIOB_PSOR,2);}};
static inline void SB(int x) {if(!x) {SETONEBIT(GPIOB_PCOR,0);} else {SETONEBIT(GPIOB_PSOR,0);}};
static inline void LAT(int x) {if(!x) {SETONEBIT(GPIOB_PCOR,1);} else {SETONEBIT(GPIOB_PSOR,1);}};
static inline void SCK(int x) {if(!x) {SETONEBIT(GPIOC_PCOR,8);} else {SETONEBIT(GPIOC_PSOR,8);}};
static inline void SDA(int x) {if(!x) {SETONEBIT(GPIOC_PCOR,9);} else {SETONEBIT(GPIOC_PSOR,9);}};
static inline void ROW0(int x) {if(!x) {SETONEBIT(GPIOA_PCOR,13);} else {SETONEBIT(GPIOA_PSOR,13);}};
static inline void ROW1(int x) {if(!x) {SETONEBIT(GPIOD_PCOR,2);} else {SETONEBIT(GPIOD_PSOR,2);}};
static inline  void ROW2(int x) {if(!x) {SETONEBIT(GPIOD_PCOR,4);} else {SETONEBIT(GPIOD_PSOR,4);}};
static inline void ROW3(int x) {if(!x) {SETONEBIT(GPIOD_PCOR,6);} else {SETONEBIT(GPIOD_PSOR,6);}};
static inline void ROW4(int x) {if(!x) {SETONEBIT(GPIOD_PCOR,7);} else {SETONEBIT(GPIOD_PSOR,7);}};
static inline void ROW5(int x) {if(!x) {SETONEBIT(GPIOD_PCOR,5);} else {SETONEBIT(GPIOD_PSOR,5);}};
static inline void ROW6(int x) {if(!x) {SETONEBIT(GPIOA_PCOR,12);} else {SETONEBIT(GPIOA_PSOR,12);}};
static inline void ROW7(int x) {if(!x) {SETONEBIT(GPIOA_PCOR,4);} else {SETONEBIT(GPIOA_PSOR,4);}};

// Processus d'initialisation de la matrice de LEDs
void matrix_init(){

  // Mise en marche des horloges
  SIM_SCGC5 |= 0x00001E00;

  PORTB_PCR0  = 256;
  PORTB_PCR1  = 256;
  PORTB_PCR2  = 256;
  PORTC_PCR8  = 256;
  PORTC_PCR9  = 256;
  PORTA_PCR13 = 256;
  PORTD_PCR2  = 256;
  PORTD_PCR4  = 256;
  PORTD_PCR6  = 256;
  PORTD_PCR7  = 256;
  PORTD_PCR5  = 256;
  PORTA_PCR12 = 256;
  PORTA_PCR4  = 256;

  GPIOA_PDDR |= ( (1<<4) | (1<<12) | (1<<13) );
  GPIOB_PDDR |= ( (1<<0) | (1<<1) | (1<<2) );
  GPIOC_PDDR |= ( (1<<8) | (1<<9) );
  GPIOD_PDDR |= ((1<<2) | (1<<4) | (1<<5) | (1<<6) | (1<<7) );

  RST(0);
  SB(1);
  LAT(1);
  SCK(0);
  SDA(0);
  ROW0(0);
  ROW1(0);
  ROW2(0);
  ROW3(0);
  ROW4(0);
  ROW5(0);
  ROW6(0);
  ROW7(0);

  for(int j = 0 ;  j<1000000 ; j++)
    asm volatile ("nop");

  RST(1);
}
