#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"

void (kbc_ih)	();
int (kb_subscribe)(uint8_t *bit_no);
int (kb_unsubscribe)();
int (utils_sys_inb)(int port, uint8_t *val);
void (enable_interrupts)();
