#include <stdint.h>

#define SETONEBIT(reg,shift) (reg |= (1<<shift))
#define CLEARONEBIT(reg,shift) (reg &= ~(1<<shift))
