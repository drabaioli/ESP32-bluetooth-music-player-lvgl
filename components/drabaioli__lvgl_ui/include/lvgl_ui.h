#ifndef LVGL_UI
#define LVGL_UI

#include <lvgl.h>

// Tell LVGL how to draw on display
typedef void (*lvgl_flush_cb_t)( struct _lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p );

void setup_lvgl_ui( size_t resolution_w, size_t resolution_h, lvgl_flush_cb_t lvgl_flush_cb );

// Notify LVGL when the display buffer has been flushed. Must be used to trigger next frame rendering
void data_drawn();

#endif // LVGL_UI
