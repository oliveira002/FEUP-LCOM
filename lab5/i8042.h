#ifndef _I8042_
#define _I8042_

#include <lcom/lcf.h>

#define STAT_REG 0x64
#define OUT_BUF 0x60
#define CMD1 0x20
#define CMD2 0X60
#define INT  BIT(0)
#define IRQ_KB 1
#define ERROR_PARITY_TIMEOUT  (BIT(6) | BIT(7))
#define WAIT_KBC    20000
#define KBC_OBF  BIT(0)
#define KBC_AUX  BIT(5)
#define DEFSCAN 0xe0
#define ESCSCAN 0x81
#define OBF_AUX  (BIT(0) | BIT(5))



#endif
