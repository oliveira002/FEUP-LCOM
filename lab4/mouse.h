#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include "i8042.h"
#include <lcom/lcf.h>

#define MIN_SLOPE 1.0

typedef enum { INIT, DRAW_UP, DRAW_DOWN,DETECTED } state_t;
typedef enum { RBDOWN, RBUP, LBDOWN, LBUP, MBDOWN,MBUP, MOVE } event_type_t;

typedef struct {
  event_type_t type;
  uint8_t moveX;
  uint8_t moveY;
  bool lbdown, rbdown, mbdown;
} mouse_event_t;


void (mouse_ih)();
int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
int (send_mouse_cmd)(uint8_t cmd);
int (utils_sys_inb)(int port, uint8_t *val);
void (mouse_set_packet)(struct packet *pacote);
int (check_ibf_full)();
int (mouse_disable_data_reporting)();
bool (check_output_buffer)();
int (gesture_handler)(uint8_t x_len, uint8_t tolerance, struct packet *pack);

#endif
