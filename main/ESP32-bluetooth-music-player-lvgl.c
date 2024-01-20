#include "ili9488_display.h"
#include "lvgl_ui.h"
#include "rotary_encoder_ky040.h"

#include "ui/ui.h"
#include "ui/ui_logic.h"

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


static state_t g_state;

static void button_single_click_cb( void *arg, void *usr_data )
{
  ESP_LOGI( "DIEGO", "BUTTON_SINGLE_CLICK" );
}


static void IRAM_ATTR encoder_position_cb( position_event_t event )
{
  ESP_LOGI( "DIEGO", "EVENT %s", event == ENCODER_POSITION_INCREMENT ? "INCREMENT" : "DECREMENT" );
  ui_action( &g_state, event == ENCODER_POSITION_INCREMENT ? MOVE_RIGHT : MOVE_LEFT );
  ESP_LOGI( "DIEGO", "COMPONENT %i", g_state.active_component );
}


void app_main(void)
{
  // Setup KY040 rotary encoder
  rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle = NULL;
  ESP_ERROR_CHECK( new_rotaty_encoder_ky040( &rotaty_encoder_ky040_handle ) );

  rotaty_encoder_ky040_register_button_cb(   rotaty_encoder_ky040_handle, BUTTON_SINGLE_CLICK, button_single_click_cb, NULL );
  rotaty_encoder_ky040_register_position_cb( rotaty_encoder_ky040_handle, encoder_position_cb );

  // Setup ili9488 display
  setup_display( notify_lvgl_flush_ready,
                 get_lvgl_display_driver(),
                 compute_buffer_size( ILI9488_DISPLAY_W, ILI9488_DISPLAY_H ) );

  // Setup lvgl
  setup_lvgl_ui( ILI9488_DISPLAY_W, ILI9488_DISPLAY_H, get_lcd_handle() );

  // Initialize gui
  ui_init();

  ui_logic_init( &g_state );

  while( 1 )
  {
    vTaskDelay( pdMS_TO_TICKS( 10 ) );
    lv_timer_handler();
  }
}
