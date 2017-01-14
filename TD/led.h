#ifndef LED_H
#define LED_H

// Définition des registres des horloges
#define SIM_SCGC5 (*(volatile uint32_t *)0x40048038)

// Définition des registres de configuration des broches en GPIO
#define PORTD_PCR5 (*(volatile uint32_t *)0x4004C014)
#define PORTE_PCR29 (*(volatile uint32_t *)0x4004D074)

// Définition des registres de configuration des broches en sortie
#define GPIOD_PDDR (*(volatile uint32_t *)0x400FF0D4)
#define GPIOE_PDDR (*(volatile uint32_t *)0x400FF114)

// Définition des registres d'allumage des LEDs
#define GPIOD_PCOR (*(volatile uint32_t *)0x400FF0C8)
#define GPIOE_PCOR (*(volatile uint32_t *)0x400FF108)

// Définitio des registres d'exctinction des LEDs
#define GPIOD_PSOR (*(volatile uint32_t *)0x400FF0C4)
#define GPIOE_PSOR (*(volatile uint32_t *)0x400FF104)

// Défition des registres de toggle des LEDs
#define GPIOD_PTOR (*(volatile uint32_t *)0x400FF0CC)
#define GPIOE_PTOR (*(volatile uint32_t *)0x400FF10C)

// Processus d'initialisation des LEDs
void led_init(void);

// Processus de gestion da LED verte
void led_g_on(void);
void led_g_off(void);
void led_g_toggle(void);

// Processus de gestion de la LED rouge
void led_r_on(void);
void led_r_off(void);
void led_r_toggle(void);

#endif
