#ifndef LED_H
#define LED_H

// Processus d'initialisation des LEDs
void led_init(void);

// Processus de gestion de la LED verte
void led_g_on(void);
void led_g_off(void);
void led_g_toggle(void);

// Processus de gestion de la LED rouge
void led_r_on(void);
void led_r_off(void);
void led_r_toggle(void);

#endif //LED_H
