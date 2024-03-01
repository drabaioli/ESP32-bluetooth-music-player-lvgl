#ifndef LVGL_UI
#define LVGL_UI

#include <esp_lcd_types.h>
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>

void   setup_lvgl_ui( size_t resolution_w, size_t resolution_h, esp_lcd_panel_handle_t lcd_handle );
void * get_lvgl_display_driver();
size_t compute_buffer_size( size_t resolution_w, size_t resolution_h );
bool   notify_lvgl_flush_ready( esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t * edata, void * user_ctx );

#endif // LVGL_UI
