#include "ili9488_display.h"
#include "lvgl_ui.h"
#include "rotary_encoder_ky040.h"

#include "ui/ui.h"
#include "ui/ui_logic.h"

#include <freertos/FreeRTOS.h>


static state_t g_state;

static void button_single_click_cb( void *arg, void *usr_data )
{
  ui_action( &g_state, PRESS );
}


static void IRAM_ATTR encoder_position_cb( position_event_t event )
{
  ui_action( &g_state, event == ENCODER_POSITION_INCREMENT ? MOVE_RIGHT : MOVE_LEFT );
}


bool display_flushed_cb( esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t * edata, void * user_ctx )
{
  data_drawn();
  return false;
}


void lvgl_flush_cb( lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_map )
{
  draw_bitmap( area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_map );
}


void app_main(void)
{
  // Setup KY040 rotary encoder
  rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle = NULL;
  ESP_ERROR_CHECK( new_rotaty_encoder_ky040( &rotaty_encoder_ky040_handle ) );

  rotaty_encoder_ky040_register_button_cb(   rotaty_encoder_ky040_handle, BUTTON_SINGLE_CLICK, button_single_click_cb, NULL );
  rotaty_encoder_ky040_register_position_cb( rotaty_encoder_ky040_handle, encoder_position_cb );

  // Setup ili9488 display
  setup_display( display_flushed_cb );

  // Setup lvgl
  setup_lvgl_ui( ILI9488_DISPLAY_W, ILI9488_DISPLAY_H, lvgl_flush_cb );

  // Initialize gui
  ui_init();

  ui_logic_init( &g_state );

  while( 1 )
  {
    vTaskDelay( pdMS_TO_TICKS( 10 ) );
    lv_timer_handler();
  }
}
