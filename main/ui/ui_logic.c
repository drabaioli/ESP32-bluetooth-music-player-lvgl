#include "ui_logic.h"

#include "ui.h"
#include "core/lv_obj.h"


static void update_ui_components( state_t * state )
{
  lv_imgbtn_set_state( ui_playBtn,     LV_IMGBTN_STATE_RELEASED );
  lv_imgbtn_set_state( ui_previousBtn, LV_IMGBTN_STATE_RELEASED );
  lv_imgbtn_set_state( ui_nextBtn,     LV_IMGBTN_STATE_RELEASED );
  lv_imgbtn_set_state( ui_volumeBtn,   LV_IMGBTN_STATE_RELEASED );
  lv_imgbtn_set_state( ui_muteBtn,     LV_IMGBTN_STATE_RELEASED );
  
  switch( state->active_component )
  {
    case VOLUME_BAR:
      lv_imgbtn_set_state( ui_volumeBtn, LV_IMGBTN_STATE_PRESSED );
      break;
    case BACK:
      lv_imgbtn_set_state( ui_previousBtn, LV_IMGBTN_STATE_PRESSED );
      break;
    case PLAY_PAUSE:
      lv_imgbtn_set_state( ui_playBtn, LV_IMGBTN_STATE_PRESSED );
      break;
    case FORWARD:
      lv_imgbtn_set_state( ui_nextBtn, LV_IMGBTN_STATE_PRESSED );
      break;
    case VOLUME_MUTE:
      lv_imgbtn_set_state( ui_muteBtn, LV_IMGBTN_STATE_PRESSED );
      break;
  }
}


static void _ui_decrease_volume()
{
  int32_t new_value = lv_slider_get_value( ui_volumeBar ) - 5;
  if( new_value < 0 )
    new_value = 0;
  lv_slider_set_value( ui_volumeBar, new_value, LV_ANIM_ON );
}


static void _ui_increase_volume()
{
  int32_t new_value = lv_slider_get_value( ui_volumeBar ) + 5;
  if( new_value > 100 )
    new_value = 100;
  lv_slider_set_value( ui_volumeBar, new_value, LV_ANIM_ON );
}


void ui_logic_init( state_t * state )
{
  state->active_component = PLAY_PAUSE;
  state->control_volume = false;
  update_ui_components( state );
}


void ui_action( state_t * state, action_t action )
{
  if( action == MOVE_LEFT )
  {
    if( state->control_volume )
      _ui_decrease_volume();
    else if( state->active_component != VOLUME_BAR )
      state->active_component--;
  }
  else if( action == MOVE_RIGHT )
  {
    if( state->control_volume )
      _ui_increase_volume();
    else if( state->active_component != VOLUME_MUTE )
      state->active_component++;
  }
  else if( action == PRESS )
  {
    if( state->active_component == VOLUME_BAR )
      state->control_volume = !state->control_volume;
  }

  update_ui_components( state );
}
