# KY-040 rotary encoder ESP-IDF Component

This ESP-IDF component handles the setup and event handling of a KY-040 rotary encoder. Uses `espressif/button` IDF component to handle button press events and debouncing logic.

# API

## rotaty_encoder_ky040_handle_t
**`typedef struct rotaty_encoder_ky040_t * rotaty_encoder_ky040_handle_t`**<br>
Handle to a rotary encoder object.

## position_event_t
**`typedef enum position_event_t`**<br>
Enumeration representing position events generated by the rotary encoder. Positions can be either `ENCODER_POSITION_INCREMENT` or `ENCODER_POSITION_DECREMENT`.

## encoder_position_cb_t
**`typedef void (* encoder_position_cb_t)( position_event_t event )`**<br>
Signature of a callback function invoked when the rotary encoder is either incremented or decremented.

## new_rotaty_encoder_ky040
**`esp_err_t new_rotaty_encoder_ky040( rotaty_encoder_ky040_handle_t * rotaty_encoder_ky040_handle )`**<br>
Creates a new rotary encoder internal structure and returns a handle to it.

### input
**`rotaty_encoder_ky040_handle_t * rotaty_encoder_ky040_handle`**<br>
A `rotaty_encoder_ky040_handle_t` pointer where the `new_rotaty_encoder_ky040` function will return the encoder handle.

### return
A `esp_err_t` error code. `ESP_OK` is returned if the function succeeds.

## rotaty_encoder_ky040_register_button_cb
**`void rotaty_encoder_ky040_register_button_cb( rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle, button_event_t event, button_cb_t cb, void * usr_data )`**<br>
Register a callback to handle button events.

### input
**`rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle`**<br>
Handle to the rotary encoder.

**`button_event_t event`**<br>
Button event type to accept (eg. `BUTTON_SINGLE_CLICK`).

**`button_cb_t cb`**<br>
Callback to handle the button event. Callback signature must be `void (* button_cb_t)(void * button_handle, void * usr_data)`.

**`void * usr_data`**<br>
Optional pointer to data passed to the callback.

## rotaty_encoder_ky040_register_position_cb
**`void rotaty_encoder_ky040_register_position_cb( rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle, encoder_position_cb_t cb )`**<br>
Register a callback to handle encoder position change events.

### input
**`rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle`**<br>
Handle to the rotary encoder.

**`encoder_position_cb_t cb`**<br>
Callback invoked on encoder position change events.

# Sample usage

```c
static void button_single_click_cb( void *arg, void *usr_data )
{
  ESP_LOGI( "MYAPP", "Button pressed!" );
}

static void IRAM_ATTR encoder_position_cb( position_event_t event )
{
  ESP_LOGI( "MYAPP", "Encoder %S", event == ENCODER_POSITION_INCREMENT ? "incremented" : "decremented" );
}

void app_main(void)
{
  // Setup KY040 rotary encoder
  rotaty_encoder_ky040_handle_t rotaty_encoder_ky040_handle = NULL;
  ESP_ERROR_CHECK( new_rotaty_encoder_ky040( &rotaty_encoder_ky040_handle ) );

  rotaty_encoder_ky040_register_button_cb(   rotaty_encoder_ky040_handle, BUTTON_SINGLE_CLICK, button_single_click_cb, NULL );
  rotaty_encoder_ky040_register_position_cb( rotaty_encoder_ky040_handle, encoder_position_cb );
}
```

# Pinout

|  pin name |  value |
| ------------ | ------------ |
| KY040_SW | 27 |
| KY040_DT | 26 |
| KY040_CLK | 25 |
