#ifndef UI_LOGIC
#define UI_LOGIC

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


typedef enum
{
  VOLUME_BAR = 0,
  BACK,
  PLAY_PAUSE,
  FORWARD,
  VOLUME_MUTE
} ui_component_t;


typedef struct
{
  ui_component_t active_component;
  bool           control_volume;
} state_t;


typedef enum
{
  MOVE_LEFT = 0,
  MOVE_RIGHT,
  PRESS,
  LONG_PRESS
} action_t;


void ui_logic_init( state_t * state );

void ui_action( state_t * state, action_t action );

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif // UI_LOGIC
