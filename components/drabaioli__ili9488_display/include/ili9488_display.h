#ifndef ILI9488_DISPLAY
#define ILI9488_DISPLAY

#include <esp_lcd_panel_io.h>

#define ILI9488_DISPLAY_W 480
#define ILI9488_DISPLAY_H 320

void setup_display( esp_lcd_panel_io_color_trans_done_cb_t color_transfered_cb, // Pass notify_lvgl_flush_ready as color_transfered_cb
                    void *                                 spi_driver_user_ctx, // Pass lv_disp_drv_t as spi_driver_user_ctx
                    size_t                                 buffer_size );       // Pass LV_BUFFER_SIZE as buffer_size

esp_lcd_panel_handle_t get_lcd_handle();

#endif // ILI9488_DISPLAY
