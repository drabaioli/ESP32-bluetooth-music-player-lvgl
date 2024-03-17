# ILI9488 Display ESP-IDF Component

This ESP-IDF component sets up a ILI9488 display and returns a `esp_lcd_panel_handle_t` handle to it.

# API

## setup_display
**`esp_lcd_panel_handle_t setup_display( esp_lcd_panel_io_color_trans_done_cb_t color_transfered_cb )`**

Sets up a ili9488 display and returns a handle to it.

### input
**`esp_lcd_panel_io_color_trans_done_cb_t color_transfered_cb`**
A callback that will be called once the pixels have been transfered to the display when calling the `draw_bitmap` function.

### return
A `esp_lcd_panel_handle_t` ldc handle.

## draw_bitmap
**`void draw_bitmap( int x1, int y1, int x2, int y2, void * color_map )`**

Request to draw pixels on screen with an offset.

### input
**`int x1, int y1`**
Top-left corner offset where to start drawing the sprite pointed by `color_map`.

**`int x2, int y2`**
Bottom-right corner offset where to stop drawing the sprite pointed by `color_map`.

**`void * color_map`**
Pointer to the pixels to draw. The sprite will have width `x2 - x1` and height `y2 - y1`.

# Sample usage

```c
bool display_flushed_cb( esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t * edata, void * user_ctx )
{
  // Notify LVGL pixels were transfered to display
  return false;
}

void app_main(void)
{
  // Setup ili9488 display
  setup_display( display_flushed_cb );
}
```

# Pinout

|  pin name |  value |
| ------------ | ------------ |
| SPI_MISO | 32 |
| SPI_MOSI | 2 |
| SPI_CLOCK | 23 |
| TFT_CS | 15 |
| TFT_RESET | 21 |
| TFT_DC | 4 |
| TFT_BACKLIGHT | 18 |
