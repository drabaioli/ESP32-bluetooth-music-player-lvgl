#ifndef ILI9488_DISPLAY
#define ILI9488_DISPLAY

#include <esp_lcd_panel_io.h>

#define ILI9488_DISPLAY_W 480
#define ILI9488_DISPLAY_H 320

esp_lcd_panel_handle_t setup_display( esp_lcd_panel_io_color_trans_done_cb_t color_transfered_cb );
void draw_bitmap( int x1, int y1, int x2, int y2, void * color_map );

#endif // ILI9488_DISPLAY
