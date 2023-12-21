file( GLOB UI_SOURCES ui/*.c )

idf_component_register(SRCS "ESP32-bluetooth-music-player-lvgl.c" "${UI_SOURCES}" INCLUDE_DIRS "." "ui/")
