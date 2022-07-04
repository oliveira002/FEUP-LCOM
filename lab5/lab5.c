// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "vbeMacros.h"
#include "i8042.h"
#include "keyboard.h"


// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {

  if(video_set_graphics(mode) != 0) {return 1;}

  sleep(delay);

  vg_exit();
  

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
                            
  if(video_set_graphics(mode) != 0) {return 1;};

  if(vg_draw_rectangle(x,y,width,height,color) != 0) {return 1;}
  
  extern uint8_t scode;
  extern int flag;
  uint8_t array[2];
  int ipc_status;
  message msg;
  int r;
  int idx = 0;
  uint8_t bit_no;
  if(kb_subscribe(&bit_no) != 0) {return 1;}
  uint32_t irq_set = BIT(bit_no);
  while(scode != ESCSCAN) { /* You may want to use a different condition */
        /* Get a request message. */
        if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
          printf("driver_receive failed with: %d", r);
          continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE: /* hardware interrupt notification */
                
                if (msg.m_notify.interrupts & irq_set) { /* subscri ... process it */
                  kbc_ih();
                  if(flag == 0) {
                    if(idx == 0) {
                      array[idx] = scode;
                      if(scode == DEFSCAN) {
                        idx = 1;
                      }
                      else {
                        kbd_print_scancode(!(scode & BIT(7)),(idx + 1),array);
                      }
                    }
                    else {
                      array[idx] = scode;
                      idx = 0;
                      kbd_print_scancode(!(scode & BIT(7)),(idx + 2),array);
                    }
                  }
                }
                break;
              default:
                break; /* no other notifications expected: do nothi*/
            }
        }
  }
  if(kb_unsubscribe() != 0) {return 1;}
  if(vg_exit() != 0) {return 1;}
  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

  if(video_set_graphics(mode) != 0) {return 1;}
  if(vg_draw_matrix(mode,no_rectangles,first,step) != 0) {return 1;}
  extern uint8_t scode;
  extern int flag;
  uint8_t array[2];
  int ipc_status;
  message msg;
  int r;
  int idx = 0;
  uint8_t bit_no;
  if(kb_subscribe(&bit_no) != 0) {return 1;}
  uint32_t irq_set = BIT(bit_no);
  while(scode != ESCSCAN) { /* You may want to use a different condition */
        /* Get a request message. */
        if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
          printf("driver_receive failed with: %d", r);
          continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE: /* hardware interrupt notification */
                
                if (msg.m_notify.interrupts & irq_set) { /* subscri ... process it */
                  kbc_ih();
                  if(flag == 0) {
                    if(idx == 0) {
                      array[idx] = scode;
                      if(scode == DEFSCAN) {
                        idx = 1;
                      }
                      else {
                        kbd_print_scancode(!(scode & BIT(7)),(idx + 1),array);
                      }
                    }
                    else {
                      array[idx] = scode;
                      idx = 0;
                      kbd_print_scancode(!(scode & BIT(7)),(idx + 2),array);
                    }
                  }
                }
                break;
              default:
                break; /* no other notifications expected: do nothi*/
            }
        }
  }
  if(kb_unsubscribe() != 0) {return 1;}
  if(vg_exit() != 0) {return 1;}

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {


  if(video_set_graphics(0x105) != 0) {return 1;}

  xpm_image_t img;
  uint8_t *map;
  map = xpm_load(xpm,XPM_INDEXED,&img);
  
  if(draw_pix_map(x,y,map,img) != 0) {return 1;}
  

  extern uint8_t scode;
  extern int flag;
  uint8_t array[2];
  int ipc_status;
  message msg;
  int r;
  int idx = 0;
  uint8_t bit_no;
  if(kb_subscribe(&bit_no) != 0) {return 1;}
  uint32_t irq_set = BIT(bit_no);
  while(scode != ESCSCAN) { /* You may want to use a different condition */
        /* Get a request message. */
        if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
          printf("driver_receive failed with: %d", r);
          continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE: /* hardware interrupt notification */
                
                if (msg.m_notify.interrupts & irq_set) { /* subscri ... process it */
                  kbc_ih();
                  if(flag == 0) {
                    if(idx == 0) {
                      array[idx] = scode;
                      if(scode == DEFSCAN) {
                        idx = 1;
                      }
                      else {
                        kbd_print_scancode(!(scode & BIT(7)),(idx + 1),array);
                      }
                    }
                    else {
                      array[idx] = scode;
                      idx = 0;
                      kbd_print_scancode(!(scode & BIT(7)),(idx + 2),array);
                    }
                  }
                }
                break;
              default:
                break; /* no other notifications expected: do nothi*/
            }
        }
  }
  if(kb_unsubscribe() != 0) {return 1;}
  if(vg_exit() != 0) {return 1;}

  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {

  if(video_set_graphics(0x105) != 0) {return 1;}

  xpm_image_t img;
  uint8_t *map;
  map = xpm_load(xpm,XPM_INDEXED,&img);
  draw_pix_map(xi,yi,map,img);

  extern int counter;
  extern uint8_t scode;
  extern int flag;
  uint8_t array[2];
  int ipc_status;
  message msg;
  int r;
  int idx = 0;
  uint8_t bit_no, bit_no_timer;
  timer_subscribe_int(&bit_no_timer);
  kb_subscribe(&bit_no);
  uint32_t irq_set = BIT(bit_no);
  uint32_t irq_set_timer = BIT(bit_no_timer);
  uint16_t interruptPerFrame = sys_hz() / fr_rate;
  uint16_t numFrames = 0;


  while(scode != ESCSCAN) { /* You may want to use a different condition */
        /* Get a request message. */
        if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
          printf("driver_receive failed with: %d", r);
          continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE: /* hardware interrupt notification */
                
                if (msg.m_notify.interrupts & irq_set) { /* subscri ... process it */
                  kbc_ih();
                  if(flag == 0) {
                    if(idx == 0) {
                      array[idx] = scode;
                      if(scode == DEFSCAN) {
                        idx = 1;
                      }
                      else {
                        kbd_print_scancode(!(scode & BIT(7)),(idx + 1),array);
                      }
                    }
                    else {
                      array[idx] = scode;
                      idx = 0;
                      kbd_print_scancode(!(scode & BIT(7)),(idx + 2),array);
                    }
                  }
                }

                if(msg.m_notify.interrupts & irq_set_timer) {
                  timer_int_handler();
                  if(counter % interruptPerFrame == 0 && ((xi != xf) || (yi != yf))) { // if se mova
                    if(speed > 0) {
                      clear_pix_map(xi,yi,img);
                      if(yi == yf) {
                        if(xi + speed > xf) {
                          xi = xf;
                        }
                        else {
                          xi += speed;
                        }
                      }
                      else if(xi == xf) {
                        if(yi + speed > yf) {
                          yi = yf;
                        }
                        else {
                          yi += speed;
                        }
                      }
                      draw_pix_map(xi,yi,map,img);
                    }
                    else {
                      if(counter % interruptPerFrame == 0) {
                        numFrames++;
                      }
                      if(numFrames % (speed * -1) == 0) {
                        clear_pix_map(xi,yi,img);
                        if(yi == yf) {
                          if(xi + 1 > xf) {
                            xi = xf;
                          }
                          else {
                            xi++;
                          }
                        }
                        else if(xi == xf) {
                          if(yi + 1 > yf) {
                            yi = yf;
                          }
                          else {
                            yi++;
                          }
                        }
                        draw_pix_map(xi,yi,map,img);
                      }
                    }
                  }
                }
                break;
              default:
                break; /* no other notifications expected: do nothi*/
            }
        }
  }
  if(timer_unsubscribe_int() != 0) {return 1;}
  if(kb_unsubscribe() != 0) {return 1;}
  if(vg_exit() != 0) {return 1;}

  return 0;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
