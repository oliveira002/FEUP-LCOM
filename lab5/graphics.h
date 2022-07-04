#ifndef _LCOM_GRAPHICS_H_
#define _LCOM_GRAPHICS_H_

#include <lcom/lcf.h>
#include "vbeMacros.h"

int (video_set_graphics)(uint16_t mode);
int(vg_draw_matrix)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step);
int (draw_pix_map)(uint16_t x, uint16_t y, uint8_t *map, xpm_image_t img);
int (clear_pix_map)(uint16_t x, uint16_t y, xpm_image_t img);
#endif
