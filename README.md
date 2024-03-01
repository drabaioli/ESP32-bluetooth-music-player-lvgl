# Build your own bluetooth speaker!

Use your Esp32 to play and control music from a bluetooth audio source.

This is work in progress, but this is the idea so far:

![Components](/img/bluetooth_music_player.jpg)

# Required components

- **Esp32**: either use a [dev kit](https://www.amazon.com/Freenove-ESP32-WROVER-Bluetooth-Compatible-Tutorials/dp/B09BC5CNHM?th=1 "dev kit") or design your pcb (mine will come soon!) 
- [**KY-040**](https://components101.com/modules/KY-04-rotary-encoder-pinout-features-datasheet-working-application-alternative "**KY-040**") rotary encoder
- [**ILI9488**](https://nl.aliexpress.com/item/32985467436.html "**ILI9488**") 3.5" TFT display. There's 2 version of this display: with and without touch screen. This project does not use the touch screen.

# Build

Instal the Expressif IDF framework or just make your life easier and just use the `espressif/idf` docker image.

## Set Esp32 target

`docker run --rm -v $PWD:/project -w /project -u $UID -e HOME=/tmp -it espressif/idf idf.py set-target esp32`

## Configure the project

`docker run --rm -v $PWD:/project -w /project -u $UID -e HOME=/tmp -it espressif/idf idf.py menuconfig`

In this step you can choose your configuration, like the preferred pinout. For the default configuration and pinout look below.

## Build the project

`docker run --rm -v $PWD:/project -w /project -u $UID -e HOME=/tmp -it espressif/idf idf.py build`

## Flash on Esp32 and monitor logging

`docker run --rm -v $PWD:/project -w /project -e HOME=/tmp --privileged -it espressif/idf idf.py -p /dev/ttyUSB0 flash monitor`

**Note:** you need to give the container permission to access the Esp device.

# Project structure

```md
├── CMakeLists.txt                      : Project's CMake file
├── components
│   ├── drabaioli__ili9488_display      : IDF component to handle ILI9488 TFT display
│   ├── drabaioli__lvgl_ui              : IDF component to handle LVGL grapical library bootstrap
│   └── drabaioli__rotary_encoder_ky040 : IDF component to handle KY-040 rotary encoder 
└── main                                : Main component logic
    └── ui                              : GUI
```

All components are designed to be reusable.

# Default configuration

## ILI9488 pinout

|  pin name |  value |
| ------------ | ------------ |
| SPI_MISO | 32 |
| SPI_MOSI | 2 |
| SPI_CLOCK | 23 |
| TFT_CS | 15 |
| TFT_RESET | 21 |
| TFT_DC | 4 |
| TFT_BACKLIGHT | 18 |

# KY-040 pinout

|  pin name |  value |
| ------------ | ------------ |
| KY040_SW | 27 |
| KY040_DT | 26 |
| KY040_CLK | 25 |
