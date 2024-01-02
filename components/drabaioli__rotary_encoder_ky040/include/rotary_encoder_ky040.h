#ifndef ROTARY_ENCODER_KY040
#define ROTARY_ENCODER_KY040

#include <iot_button.h>

#ifdef __cplusplus
extern "C" {
#endif

////
// Type declarations

// Make rotaty_encoder_ky040_t internal details opaque, except for button_event_t
typedef struct rotaty_encoder_ky040_t * rotaty_encoder_ky040_handle_t;

typedef enum
{
  ENCODER_POSITION_INCREMENT = 0,
  ENCODER_POSITION_DECREMENT,
} position_event_t;

typedef void (* encoder_position_cb_t)( position_event_t event );


////
// Function declarations
esp_err_t new_rotaty_encoder_ky040( rotaty_encoder_ky040_handle_t * rotaty_encoder_ky040_handle );

void rotaty_encoder_ky040_register_button_cb(   rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle, button_event_t event, button_cb_t cb, void * usr_data );
void rotaty_encoder_ky040_register_position_cb( rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle, encoder_position_cb_t cb );

#ifdef __cplusplus
}
#endif

#endif // ROTARY_ENCODER_KY040
