#include "ili9488_display.h"
#include "lvgl_ui.h"

#include <esp_log.h>
#include <lvgl.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


static const char *TAG = "main";

static lv_style_t style_screen;

void create_ui()
{
    // Set the background color of the display to black.
    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_color_hex(0x00FF00));
    lv_obj_add_style(lv_scr_act(), &style_screen, LV_STATE_DEFAULT);
}

void update_ui()
{
    // Set the background color of the display to black.
    static unsigned int color = 0x0;
    color += 0x1;
    if( color > ( ( 1 << 16 ) - 1 ) ) color = 0x0; // 16 bits color ?
    ESP_LOGI(TAG, "DIEGO: after create_ui %i", color);
    lv_style_set_bg_color(&style_screen, lv_color_hex(color));
    lv_obj_add_style(lv_scr_act(), &style_screen, LV_STATE_DEFAULT);
}


void app_main(void)
{

  setup_display( notify_lvgl_flush_ready,
                 get_lvgl_display_driver(),
                 compute_buffer_size( ILI9488_DISPLAY_W, ILI9488_DISPLAY_H ) );

  ESP_LOGI(TAG, "DIEGO: before setup_lvgl_ui");
  setup_lvgl_ui( ILI9488_DISPLAY_W, ILI9488_DISPLAY_H, get_lcd_handle() );
  ESP_LOGI(TAG, "DIEGO: after setup_lvgl_ui");

  create_ui();
  ESP_LOGI(TAG, "DIEGO: after create_ui");

  while (1)
  {
    ESP_LOGI(TAG, "DIEGO: looping...");
    vTaskDelay(pdMS_TO_TICKS(100));
    update_ui();
    lv_timer_handler();
  }
}
