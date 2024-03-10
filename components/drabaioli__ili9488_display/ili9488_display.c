/* Most of this code comes from atanisoft/esp_lcd_ili9488 example:
 * https://github.com/atanisoft/esp_lcd_ili9488/blob/main/examples/lvgl/main/main.c
 */

#include "ili9488_display.h"

#include <driver/ledc.h>
#include <driver/spi_master.h>
#include <esp_err.h>
#include <esp_log.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_ili9488.h>


static const char *TAG = "ili9488_display";

static const int          DISPLAY_COMMAND_BITS   = 8;
static const int          DISPLAY_PARAMETER_BITS = 8;
static const unsigned int DISPLAY_REFRESH_HZ     = 40000000;
static const int          DISPLAY_SPI_QUEUE_LEN  = 10;
static const int          SPI_MAX_TRANSFER_SIZE  = 32768;

static const ledc_mode_t      BACKLIGHT_LEDC_MODE             = LEDC_LOW_SPEED_MODE;
static const ledc_channel_t   BACKLIGHT_LEDC_CHANNEL          = LEDC_CHANNEL_0;
static const ledc_timer_t     BACKLIGHT_LEDC_TIMER            = LEDC_TIMER_1;
static const ledc_timer_bit_t BACKLIGHT_LEDC_TIMER_RESOLUTION = LEDC_TIMER_10_BIT;
static const uint32_t         BACKLIGHT_LEDC_FRQUENCY         = 5000;

static esp_lcd_panel_io_handle_t lcd_io_handle = NULL;
static esp_lcd_panel_handle_t    lcd_handle    = NULL;


static void display_brightness_init(void)
{
  const ledc_channel_config_t LCD_backlight_channel =
  {
    .gpio_num = (gpio_num_t)CONFIG_TFT_BACKLIGHT_PIN,
    .speed_mode = BACKLIGHT_LEDC_MODE,
    .channel = BACKLIGHT_LEDC_CHANNEL,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = BACKLIGHT_LEDC_TIMER,
    .duty = 0,
    .hpoint = 0,
    .flags = 
    {
      .output_invert = 0
    }
  };
  const ledc_timer_config_t LCD_backlight_timer =
  {
    .speed_mode = BACKLIGHT_LEDC_MODE,
    .duty_resolution = BACKLIGHT_LEDC_TIMER_RESOLUTION,
    .timer_num = BACKLIGHT_LEDC_TIMER,
    .freq_hz = BACKLIGHT_LEDC_FRQUENCY,
    .clk_cfg = LEDC_AUTO_CLK
  };
  ESP_LOGI(TAG, "Initializing LEDC for backlight pin: %d", CONFIG_TFT_BACKLIGHT_PIN);

  ESP_ERROR_CHECK(ledc_timer_config(&LCD_backlight_timer));
  ESP_ERROR_CHECK(ledc_channel_config(&LCD_backlight_channel));
}

void display_brightness_set(int brightness_percentage)
{
  if (brightness_percentage > 100)
  {
    brightness_percentage = 100;
  }    
  else if (brightness_percentage < 0)
  {
    brightness_percentage = 0;
  }
  ESP_LOGI(TAG, "Setting backlight to %d%%", brightness_percentage);

  // LEDC resolution set to 10bits, thus: 100% = 1023
  uint32_t duty_cycle = (1023 * brightness_percentage) / 100;
  ESP_ERROR_CHECK(ledc_set_duty(BACKLIGHT_LEDC_MODE, BACKLIGHT_LEDC_CHANNEL, duty_cycle));
  ESP_ERROR_CHECK(ledc_update_duty(BACKLIGHT_LEDC_MODE, BACKLIGHT_LEDC_CHANNEL));
}


void initialize_spi()
{
  ESP_LOGI(TAG, "Initializing SPI bus (MOSI:%d, MISO:%d, CLK:%d)",
      CONFIG_SPI_MOSI, CONFIG_SPI_MISO, CONFIG_SPI_CLOCK);
  spi_bus_config_t bus =
  {
    .mosi_io_num = CONFIG_SPI_MOSI,
    .miso_io_num = CONFIG_SPI_MISO,
    .sclk_io_num = CONFIG_SPI_CLOCK,
    .quadwp_io_num = GPIO_NUM_NC,
    .quadhd_io_num = GPIO_NUM_NC,
    .data4_io_num = GPIO_NUM_NC,
    .data5_io_num = GPIO_NUM_NC,
    .data6_io_num = GPIO_NUM_NC,
    .data7_io_num = GPIO_NUM_NC,
    .max_transfer_sz = SPI_MAX_TRANSFER_SIZE,
    .flags = SPICOMMON_BUSFLAG_SCLK | SPICOMMON_BUSFLAG_MISO |
      SPICOMMON_BUSFLAG_MOSI | SPICOMMON_BUSFLAG_MASTER,
    .intr_flags = ESP_INTR_FLAG_LOWMED | ESP_INTR_FLAG_IRAM
  };

  ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &bus, SPI_DMA_CH_AUTO));
}


void initialize_display( esp_lcd_panel_io_color_trans_done_cb_t color_transfered_cb )
{
  const esp_lcd_panel_io_spi_config_t io_config = 
  {
    .cs_gpio_num = CONFIG_TFT_CS_PIN,
    .dc_gpio_num = CONFIG_TFT_DC_PIN,
    .spi_mode = 0,
    .pclk_hz = DISPLAY_REFRESH_HZ,
    .trans_queue_depth = DISPLAY_SPI_QUEUE_LEN,
    .on_color_trans_done = color_transfered_cb,
    .user_ctx = NULL,
    .lcd_cmd_bits = DISPLAY_COMMAND_BITS,
    .lcd_param_bits = DISPLAY_PARAMETER_BITS,
    .flags =
    {
      //#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
      //            .dc_as_cmd_phase = 0,
      //            .dc_low_on_data = 0,
      //            .octal_mode = 0,
      //            .lsb_first = 0
      //#else
      .dc_low_on_data = 0,
      .octal_mode = 0,
      .sio_mode = 0,
      .lsb_first = 0,
      .cs_high_active = 0
      //#endif
    }
  };

  const esp_lcd_panel_dev_config_t lcd_config = 
  {
    .reset_gpio_num = CONFIG_TFT_RESET_PIN,
    .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
    .bits_per_pixel = 18,
    .flags =
    {
      .reset_active_high = 0
    },
    .vendor_config = NULL
  };

  ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI2_HOST, &io_config, &lcd_io_handle)); 

  ESP_ERROR_CHECK(esp_lcd_new_panel_ili9488(lcd_io_handle, &lcd_config, ILI9488_DISPLAY_W * 25, &lcd_handle));

  ESP_ERROR_CHECK(esp_lcd_panel_reset(lcd_handle));
  ESP_ERROR_CHECK(esp_lcd_panel_init(lcd_handle));
  ESP_ERROR_CHECK(esp_lcd_panel_invert_color(lcd_handle, false));
  ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(lcd_handle, true)); // TODO : Diego : portrait or landscape?
  ESP_ERROR_CHECK(esp_lcd_panel_mirror(lcd_handle, true, false));
  ESP_ERROR_CHECK(esp_lcd_panel_set_gap(lcd_handle, 0, 0));
  //#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
  //    ESP_ERROR_CHECK(esp_lcd_panel_disp_off(lcd_handle, false));
  //#else
  ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(lcd_handle, true));
  //#endif
}


esp_lcd_panel_handle_t setup_display( esp_lcd_panel_io_color_trans_done_cb_t color_transfered_cb )
{
  initialize_spi();
  initialize_display( color_transfered_cb );
  display_brightness_init();
  display_brightness_set(100);
  return lcd_handle;
}


void draw_bitmap( int x1, int y1, int x2, int y2, void * color_map )
{
  esp_lcd_panel_draw_bitmap( lcd_handle, x1, y1, x2, y2, color_map );
}
