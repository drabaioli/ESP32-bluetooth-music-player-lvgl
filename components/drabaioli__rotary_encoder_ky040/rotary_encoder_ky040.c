#include "rotary_encoder_ky040.h"

#include <esp_log.h>
#include <esp_check.h>

#include <driver/pulse_cnt.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

static const char *TAG = "ROTARY_ENCODER_KY040";

#define KY040_BUTTON_LONG_PRESS_TIME  1000
#define KY040_BUTTON_SHORT_PRESS_TIME    1

#define PCNT_HIGH_LIMIT    4
#define PCNT_LOW_LIMIT    -4


typedef struct
{
  button_handle_t       gpio_btn;
  pcnt_unit_handle_t    pcnt_unit;
  pcnt_channel_handle_t pcnt_chan_a;
  pcnt_channel_handle_t pcnt_chan_b;
  encoder_position_cb_t encoder_position_cb;
  QueueHandle_t         encoder_event_queue;
  TaskHandle_t          event_processor_task_handle;
} rotaty_encoder_ky040_t;


void event_processor_task( void * rotaty_encoder_ky040_handle )
{
  rotaty_encoder_ky040_t * rotaty_encoder_ky040 = (rotaty_encoder_ky040_t *) rotaty_encoder_ky040_handle;
  position_event_t position_event;
  while( true )
  {
    if( xQueueReceive( rotaty_encoder_ky040->encoder_event_queue, &position_event, pdMS_TO_TICKS( 100 ) ) )
    {
      if( rotaty_encoder_ky040->encoder_position_cb )
        rotaty_encoder_ky040->encoder_position_cb( position_event );
    }
  }
}

static bool watchpoint_reached_isr( pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx )
{
  BaseType_t high_task_wakeup;
  QueueHandle_t queue = (QueueHandle_t)user_ctx;
  // send event data to queue, from this interrupt callback
  position_event_t encoder_position = edata->watch_point_value == PCNT_HIGH_LIMIT ? ENCODER_POSITION_INCREMENT : ENCODER_POSITION_DECREMENT;
  xQueueSendFromISR( queue, &encoder_position, &high_task_wakeup );
  return (high_task_wakeup == pdTRUE);
}


esp_err_t new_rotaty_encoder_ky040( rotaty_encoder_ky040_handle_t * rotaty_encoder_ky040_handle )
{
  esp_err_t ret = ESP_OK;

  ESP_LOGI( TAG, "Allocate memory" );
  rotaty_encoder_ky040_t * rotaty_encoder_ky040 = (rotaty_encoder_ky040_t *) calloc( 1, sizeof( rotaty_encoder_ky040_t ) );
  ESP_GOTO_ON_FALSE( rotaty_encoder_ky040, ESP_ERR_NO_MEM, err1, TAG, "Out of memory during new_rotaty_encoder_ky040" );

  ////
  // Setup gpio button
  button_config_t gpio_btn_cfg = {
    .type = BUTTON_TYPE_GPIO,
    .long_press_time = KY040_BUTTON_LONG_PRESS_TIME,
    .short_press_time = KY040_BUTTON_SHORT_PRESS_TIME,
    .gpio_button_config = {
      .gpio_num = CONFIG_KY040_SW,
      .active_level = 0,
    },
  };
  rotaty_encoder_ky040->gpio_btn = iot_button_create( &gpio_btn_cfg );
  ESP_GOTO_ON_FALSE( rotaty_encoder_ky040->gpio_btn, ESP_FAIL, err2, TAG, "Failed creating gpio button" );

  ////
  // Setup pulse count for rotary encoder events
  ESP_LOGI( TAG, "Install pcnt unit" );
  pcnt_unit_config_t unit_config = {
      .high_limit = PCNT_HIGH_LIMIT,
      .low_limit = PCNT_LOW_LIMIT,
  };
  ESP_GOTO_ON_ERROR( pcnt_new_unit( &unit_config, &( rotaty_encoder_ky040->pcnt_unit ) ), err3, TAG, "Failed creating pcnt unit" );

  ESP_LOGI( TAG, "Set glitch filter" );
  pcnt_glitch_filter_config_t filter_config = {
      .max_glitch_ns = 10000,
  };
  ESP_GOTO_ON_ERROR( pcnt_unit_set_glitch_filter( rotaty_encoder_ky040->pcnt_unit, &filter_config ), err4, TAG, "Failed installing glitch filter" );

  ESP_LOGI( TAG, "Install pcnt channels" );
  pcnt_chan_config_t chan_a_config = {
      .edge_gpio_num = CONFIG_KY040_DT,
      .level_gpio_num = CONFIG_KY040_CLK,
  };
  ESP_GOTO_ON_ERROR( pcnt_new_channel( rotaty_encoder_ky040->pcnt_unit, &chan_a_config, &( rotaty_encoder_ky040->pcnt_chan_a ) ), err4, TAG, "Failed installing pcnt channels" );

  pcnt_chan_config_t chan_b_config = {
      .edge_gpio_num = CONFIG_KY040_CLK,
      .level_gpio_num = CONFIG_KY040_DT,
  };
  ESP_GOTO_ON_ERROR( pcnt_new_channel( rotaty_encoder_ky040->pcnt_unit, &chan_b_config, &( rotaty_encoder_ky040->pcnt_chan_b ) ), err5, TAG, "Failed installing pcnt channels" );

  ESP_LOGI( TAG, "Set edge and level actions for pcnt channels" );
  ESP_GOTO_ON_ERROR( pcnt_channel_set_edge_action(  rotaty_encoder_ky040->pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE ),
                                                    err6, TAG, "Failed setting edge and level action" );
  ESP_GOTO_ON_ERROR( pcnt_channel_set_level_action( rotaty_encoder_ky040->pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP,    PCNT_CHANNEL_LEVEL_ACTION_INVERSE ),
                                                    err6, TAG, "Failed setting edge and level action" );
  ESP_GOTO_ON_ERROR( pcnt_channel_set_edge_action(  rotaty_encoder_ky040->pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE ),
                                                    err6, TAG, "Failed setting edge and level action" );
  ESP_GOTO_ON_ERROR( pcnt_channel_set_level_action( rotaty_encoder_ky040->pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP,    PCNT_CHANNEL_LEVEL_ACTION_INVERSE ),
                                                    err6, TAG, "Failed setting edge and level action" );

  ESP_LOGI( TAG, "Add high and low watchpoints" );
  pcnt_unit_add_watch_point( rotaty_encoder_ky040->pcnt_unit, PCNT_LOW_LIMIT );
  pcnt_unit_add_watch_point( rotaty_encoder_ky040->pcnt_unit, PCNT_HIGH_LIMIT );
  pcnt_event_callbacks_t cbs = {
    .on_reach = watchpoint_reached_isr,
  };
  rotaty_encoder_ky040->encoder_event_queue = xQueueCreate( 2, sizeof( int ) );
  ESP_GOTO_ON_ERROR( pcnt_unit_register_event_callbacks( rotaty_encoder_ky040->pcnt_unit, &cbs, rotaty_encoder_ky040->encoder_event_queue ), err6, TAG, "Failed adding watchpoint" );

  ESP_LOGI( TAG, "Create event processor task" );
  BaseType_t xReturned = xTaskCreate( (TaskFunction_t)event_processor_task, "PositionEventProcessor", configMINIMAL_STACK_SIZE * 4,
                                      (void *)rotaty_encoder_ky040, 2, &rotaty_encoder_ky040->event_processor_task_handle );
  ESP_GOTO_ON_FALSE( xReturned == pdPASS, ESP_FAIL, err6, TAG, "Failed creating event processor task" );

  ESP_LOGI( TAG, "Enable pcnt unit" );
  ESP_GOTO_ON_ERROR( pcnt_unit_enable( rotaty_encoder_ky040->pcnt_unit ), err7, TAG, "Failed enabling pcnt unit" );
  ESP_LOGI( TAG, "Clear pcnt unit" );
  ESP_GOTO_ON_ERROR( pcnt_unit_clear_count( rotaty_encoder_ky040->pcnt_unit ), err7, TAG, "Failed clearing pcnt unit" );
  ESP_LOGI( TAG, "Start pcnt unit" );
  ESP_GOTO_ON_ERROR( pcnt_unit_start( rotaty_encoder_ky040->pcnt_unit ), err7, TAG, "Failed starting pcnt unit" );

  *rotaty_encoder_ky040_handle = (rotaty_encoder_ky040_handle_t)rotaty_encoder_ky040;
  return ESP_OK;

  // Clean before exit
err7:
  vTaskDelete( rotaty_encoder_ky040->event_processor_task_handle );
err6:
  pcnt_del_channel( rotaty_encoder_ky040->pcnt_chan_b );
err5:
  pcnt_del_channel( rotaty_encoder_ky040->pcnt_chan_a );
err4:
  pcnt_del_unit( rotaty_encoder_ky040->pcnt_unit );
err3:
  iot_button_delete( rotaty_encoder_ky040->gpio_btn );
err2:
  free( rotaty_encoder_ky040 );
err1:
  return ret;
}


void rotaty_encoder_ky040_register_button_cb( rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle, button_event_t event, button_cb_t cb, void *usr_data )
{
  iot_button_register_cb( ((rotaty_encoder_ky040_t *)rotaty_encoder_ky040_handle)->gpio_btn, event, cb, usr_data );
}


void rotaty_encoder_ky040_register_position_cb( rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle, encoder_position_cb_t cb )
{
  ((rotaty_encoder_ky040_t *)rotaty_encoder_ky040_handle)->encoder_position_cb = cb;
}
