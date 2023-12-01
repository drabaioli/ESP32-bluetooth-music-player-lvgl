// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.2.0
// PROJECT: MusicPlayer

#ifndef _MUSICPLAYER_UI_H
#define _MUSICPLAYER_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_screenBackground;
extern lv_obj_t * ui_detailsBackground;
extern lv_obj_t * ui_songDetails;
extern lv_obj_t * ui_timeBar;
extern lv_obj_t * ui_timeString;
extern lv_obj_t * ui_volumeBar;
extern lv_obj_t * ui_playBtn;
extern lv_obj_t * ui_previousBtn;
extern lv_obj_t * ui_nextBtn;
extern lv_obj_t * ui_volumeBtn;
extern lv_obj_t * ui_muteBtn;


LV_IMG_DECLARE(ui_img_play_png);    // assets/play.png
LV_IMG_DECLARE(ui_img_play_border_png);    // assets/play_border.png
LV_IMG_DECLARE(ui_img_back_png);    // assets/back.png
LV_IMG_DECLARE(ui_img_back_border_png);    // assets/back_border.png
LV_IMG_DECLARE(ui_img_next_png);    // assets/next.png
LV_IMG_DECLARE(ui_img_next_border_png);    // assets/next_border.png
LV_IMG_DECLARE(ui_img_volume_png);    // assets/volume.png
LV_IMG_DECLARE(ui_img_volume_border_png);    // assets/volume_border.png
LV_IMG_DECLARE(ui_img_mute_png);    // assets/mute.png
LV_IMG_DECLARE(ui_img_mute_border_png);    // assets/mute_border.png




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
