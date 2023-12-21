#include "ili9488_display.h"
#include "lvgl_ui.h"

#include <lvgl.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "ui/ui.h"

void app_main(void)
{
  // Setup ili9488 display
  setup_display( notify_lvgl_flush_ready,
                 get_lvgl_display_driver(),
                 compute_buffer_size( ILI9488_DISPLAY_W, ILI9488_DISPLAY_H ) );

  // Setup lvgl
  setup_lvgl_ui( ILI9488_DISPLAY_W, ILI9488_DISPLAY_H, get_lcd_handle() );

  // Initialize gui
  ui_init();

  while (1)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
    lv_timer_handler();
  }
}
