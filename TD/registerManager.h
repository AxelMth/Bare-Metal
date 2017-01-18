#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

// Définition des registres des horloges
#define SIM_SCGC5 (*(volatile uint32_t *) 0x40048038)

#define SETONEBIT(reg,shift) (reg |= (1<<shift))
#define CLEARONEBIT(reg,shift) (reg &= ~(1<<shift))
#define GETONEBIT(reg,shift) (reg & (1<<shift))

#endif // REGISTER_H
