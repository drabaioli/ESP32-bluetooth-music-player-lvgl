# LVGL bootstrap ESP-IDF Component

This ESP-IDF component handles all bootstrap logic to set up an LVGL UI on a ESP32 based system.

# API

## lvgl_flush_cb_t
**`typedef void (*lvgl_flush_cb_t)( lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p )`**
Signature of a callback function invoked when LVGL is ready to draw on screen. The callback function should send the pixel buffer pointed by `color_p` to the display device, and draw on a rectangle defined by `area` which represents the region of the screen where the pixels need to be drawn.

### input
**`lv_disp_drv_t * disp_drv`**
Pointer to the internal display driver.

**`const lv_area_t * area`**
Area of the screen where to draw the color buffer.

**`lv_color_t * color_p`**
Pointer to the color buffer to draw on screen.

## setup_lvgl_ui
**`void setup_lvgl_ui( size_t resolution_w, size_t resolution_h, lvgl_flush_cb_t lvgl_flush_cb )`**
Sets up LVGL ready to handle a GUI on a `resolution_w`x`resolution_h` screen. 

### input
**`size_t resolution_w`**
Width of the display.

**`size_t resolution_h`**
Height of the display.

**`lvgl_flush_cb_t lvgl_flush_cb`**
Callback function that LVGL will use to draw onto the screen.

## data_drawn
**`void data_drawn()`**
Notify LVGL that the pixel buffer has been sent to the screen and that LVGL can send a new one. Call this function when the pixels drawn during `lvgl_flush_cb_t` have been sent to the screen.

