#include "ui_logic.h"

#include "ui.h"
#include "core/lv_obj.h"

#include <esp_log.h>

static void update_ui_components( state_t * state )
{
  lv_obj_clear_state( ui_volumeBar,   LV_STATE_PRESSED );
  lv_obj_clear_state( ui_playBtn,     LV_STATE_PRESSED );
  lv_obj_clear_state( ui_previousBtn, LV_STATE_PRESSED );
  lv_obj_clear_state( ui_nextBtn,     LV_STATE_PRESSED );
  lv_obj_clear_state( ui_volumeBtn,   LV_STATE_PRESSED );
  lv_obj_clear_state( ui_muteBtn,     LV_STATE_PRESSED );
  
  switch( state->active_component )
  {
    case VOLUME_BAR:
      lv_obj_add_state( ui_volumeBar, LV_STATE_PRESSED );
      lv_obj_add_state( ui_volumeBtn, LV_STATE_PRESSED );
  ESP_LOGI( "DIEGO", "VOLUME_BAR" );
  lv_event_send( ui_volumeBar, LV_EVENT_REFRESH, NULL );
      break;
    case BACK:
      lv_obj_add_state( ui_previousBtn, LV_STATE_PRESSED );
  ESP_LOGI( "DIEGO", "BACK" );
  lv_event_send( ui_previousBtn, LV_EVENT_REFRESH, NULL );
      break;
    case PLAY_PAUSE:
      lv_obj_add_state( ui_playBtn, LV_STATE_PRESSED );
  ESP_LOGI( "DIEGO", "PLAY_PAUSE" );
  lv_event_send( ui_playBtn, LV_EVENT_REFRESH, NULL );
      break;
    case FORWARD:
      lv_obj_add_state( ui_nextBtn, LV_STATE_PRESSED );
  ESP_LOGI( "DIEGO", "FORWARD" );
  lv_event_send( ui_nextBtn, LV_EVENT_REFRESH, NULL );
      break;
    case VOLUME_MUTE:
      lv_obj_add_state( ui_muteBtn, LV_STATE_PRESSED );
  ESP_LOGI( "DIEGO", "VOLUME_MUTE" );
  lv_event_send( ui_muteBtn, LV_EVENT_REFRESH, NULL );
      break;
  }
  lv_event_send( ui_Screen1, LV_EVENT_REFRESH, NULL );
}


void ui_logic_init( state_t * state )
{
  state->active_component = PLAY_PAUSE;
  update_ui_components( state );
}


void ui_action( state_t * state, action_t action )
{
  if( action == MOVE_LEFT )
    state->active_component--;
  else if( action == MOVE_RIGHT )
    state->active_component++;

  if( state->active_component > VOLUME_MUTE )
    state->active_component = VOLUME_MUTE;
  if( state->active_component < VOLUME_BAR )
    state->active_component = VOLUME_BAR;

  update_ui_components( state );
}
