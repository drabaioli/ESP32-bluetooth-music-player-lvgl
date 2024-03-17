/* Most of this code comes from atanisoft/esp_lcd_ili9488 example:
 * https://github.com/atanisoft/esp_lcd_ili9488/blob/main/examples/lvgl/main/main.c
 */

#include "lvgl_ui.h"

#include <esp_log.h>
#include <esp_timer.h>
#include <esp_heap_caps.h>

static const char *TAG = "lvgl_ui";

static const int LVGL_UPDATE_PERIOD_MS = 5;

static lv_disp_draw_buf_t lv_disp_buf;
static lv_disp_drv_t      lv_disp_drv;
static lv_disp_t *        lv_display = NULL;
static lv_color_t *       lv_buf_1   = NULL;
static lv_color_t *       lv_buf_2   = NULL;


void data_drawn()
{
  lv_disp_flush_ready(&lv_disp_drv);
}


static void IRAM_ATTR lvgl_tick_cb(void *param)
{
  lv_tick_inc(LVGL_UPDATE_PERIOD_MS);
}


void initialize_lvgl( size_t resolution_w, size_t resolution_h, lvgl_flush_cb_t lvgl_flush_cb )
{
  const size_t lv_buffer_size = resolution_w * 25;
  ESP_LOGI(TAG, "Initializing LVGL");
  lv_init();
  ESP_LOGI(TAG, "Allocating %zu bytes for LVGL buffer", lv_buffer_size * sizeof(lv_color_t));
  lv_buf_1 = (lv_color_t *)heap_caps_malloc(lv_buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
  ESP_LOGI(TAG, "Allocating %zu bytes for second LVGL buffer", lv_buffer_size * sizeof(lv_color_t));
  lv_buf_2 = (lv_color_t *)heap_caps_malloc(lv_buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
  ESP_LOGI(TAG, "Creating LVLG display buffer");
  lv_disp_draw_buf_init(&lv_disp_buf, lv_buf_1, lv_buf_2, lv_buffer_size);

  ESP_LOGI(TAG, "Initializing %dx%d display", resolution_w, resolution_h);
  lv_disp_drv_init(&lv_disp_drv);
  lv_disp_drv.hor_res = resolution_w;
  lv_disp_drv.ver_res = resolution_h;
  lv_disp_drv.flush_cb = lvgl_flush_cb;
  lv_disp_drv.draw_buf = &lv_disp_buf;
  lv_disp_drv.user_data = NULL;
  lv_display = lv_disp_drv_register(&lv_disp_drv);

  ESP_LOGI(TAG, "Creating LVGL tick timer");
  const esp_timer_create_args_t lvgl_tick_timer_args =
  {
    .callback = &lvgl_tick_cb,
    .name = "lvgl_tick"
  };
  esp_timer_handle_t lvgl_tick_timer = NULL;
  ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, LVGL_UPDATE_PERIOD_MS * 1000));
}


void setup_lvgl_ui( size_t resolution_w, size_t resolution_h, lvgl_flush_cb_t lvgl_flush_cb )
{
  initialize_lvgl( resolution_w, resolution_h, lvgl_flush_cb );
}
