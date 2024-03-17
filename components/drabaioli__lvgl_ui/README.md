# LVGL bootstrap ESP-IDF Component

This ESP-IDF component handles all bootstrap logic to set up an LVGL UI on a ESP32 based system.

# API

## lvgl_flush_cb_t
**`typedef void (*lvgl_flush_cb_t)( lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p )`**<br>
Signature of a callback function invoked when LVGL is ready to draw on screen. The callback function should send the pixel buffer pointed by `color_p` to the display device, and draw on a rectangle defined by `area` which represents the region of the screen where the pixels need to be drawn.

### input
**`lv_disp_drv_t * disp_drv`**<br>
Pointer to the internal display driver.

**`const lv_area_t * area`**<br>
Area of the screen where to draw the color buffer.

**`lv_color_t * color_p`**<br>
Pointer to the color buffer to draw on screen.

## setup_lvgl_ui
**`void setup_lvgl_ui( size_t resolution_w, size_t resolution_h, lvgl_flush_cb_t lvgl_flush_cb )`**<br>
Sets up LVGL ready to handle a GUI on a `resolution_w`x`resolution_h` screen. 

### input
**`size_t resolution_w`**<br>
Width of the display.

**`size_t resolution_h`**<br>
Height of the display.

**`lvgl_flush_cb_t lvgl_flush_cb`**<br>
Callback function that LVGL will use to draw onto the screen.

## data_drawn
**`void data_drawn()`**<br>
Notify LVGL that the pixel buffer has been sent to the screen and that LVGL can send a new one. Call this function when the pixels drawn during `lvgl_flush_cb_t` have been sent to the screen.

# Sample usage

```c
void lvgl_flush_cb( lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_map )
{
  transfer_pixels_to_display( area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_map );
}

void app_main(void)
{
  // Setup lvgl
  setup_lvgl_ui( ILI9488_DISPLAY_W, ILI9488_DISPLAY_H, lvgl_flush_cb );

  // Draw a gui

  while( 1 )
  {
    vTaskDelay( pdMS_TO_TICKS( 10 ) );
    lv_timer_handler();
  }
}
```
