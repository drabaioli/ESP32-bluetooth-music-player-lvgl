// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.2.0
// PROJECT: MusicPlayer

#include "ui.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_screenBackground;
lv_obj_t * ui_detailsBackground;
lv_obj_t * ui_songDetails;
lv_obj_t * ui_timeBar;
lv_obj_t * ui_timeString;
lv_obj_t * ui_volumeBar;
lv_obj_t * ui_playBtn;
lv_obj_t * ui_previousBtn;
lv_obj_t * ui_nextBtn;
lv_obj_t * ui_volumeBtn;
lv_obj_t * ui_muteBtn;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_screenBackground = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_screenBackground, lv_pct(100));
    lv_obj_set_height(ui_screenBackground, lv_pct(100));
    lv_obj_set_align(ui_screenBackground, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_screenBackground, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_screenBackground, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_screenBackground, lv_color_hex(0x204C73), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_screenBackground, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_screenBackground, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_detailsBackground = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_detailsBackground, 420);
    lv_obj_set_height(ui_detailsBackground, 130);
    lv_obj_set_x(ui_detailsBackground, 0);
    lv_obj_set_y(ui_detailsBackground, 40);
    lv_obj_set_align(ui_detailsBackground, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_detailsBackground, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_detailsBackground, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_detailsBackground, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_detailsBackground, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_songDetails = lv_label_create(ui_detailsBackground);
    lv_obj_set_width(ui_songDetails, 380);
    lv_obj_set_height(ui_songDetails, 80);
    lv_obj_set_align(ui_songDetails, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_songDetails, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_songDetails, "Song:\nAlbum:\nBand:");
    lv_obj_set_style_text_color(ui_songDetails, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_songDetails, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_songDetails, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_songDetails, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_songDetails, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_songDetails, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_songDetails, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_songDetails, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_timeBar = lv_bar_create(ui_detailsBackground);
    lv_bar_set_value(ui_timeBar, 25, LV_ANIM_OFF);
    lv_obj_set_width(ui_timeBar, 380);
    lv_obj_set_height(ui_timeBar, 10);
    lv_obj_set_x(ui_timeBar, 0);
    lv_obj_set_y(ui_timeBar, 8);
    lv_obj_set_align(ui_timeBar, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_bg_color(ui_timeBar, lv_color_hex(0xAFD7FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_timeBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_timeBar, lv_color_hex(0x244C74), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_timeBar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_timeString = lv_label_create(ui_timeBar);
    lv_obj_set_width(ui_timeString, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_timeString, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_timeString, LV_ALIGN_CENTER);
    lv_label_set_text(ui_timeString, "3:05 / 5:20");
    lv_obj_set_style_text_color(ui_timeString, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_timeString, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_timeString, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_volumeBar = lv_slider_create(ui_Screen1);
    lv_slider_set_value(ui_volumeBar, 50, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_volumeBar) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_volumeBar, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_volumeBar, 10);
    lv_obj_set_height(ui_volumeBar, 100);
    lv_obj_set_x(ui_volumeBar, 10);
    lv_obj_set_y(ui_volumeBar, -20);
    lv_obj_set_align(ui_volumeBar, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_set_style_bg_color(ui_volumeBar, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_volumeBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_volumeBar, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_volumeBar, lv_color_hex(0x242424), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_volumeBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_volumeBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_volumeBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_volumeBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_volumeBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_volumeBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_volumeBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_volumeBar, lv_color_hex(0x204C73), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_volumeBar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_volumeBar, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_volumeBar, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_playBtn = lv_imgbtn_create(ui_Screen1);
    lv_imgbtn_set_src(ui_playBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_play_png, NULL);
    lv_imgbtn_set_src(ui_playBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_play_border_png, NULL);
    lv_obj_set_width(ui_playBtn, 64);
    lv_obj_set_height(ui_playBtn, 64);
    lv_obj_set_x(ui_playBtn, 0);
    lv_obj_set_y(ui_playBtn, -40);
    lv_obj_set_align(ui_playBtn, LV_ALIGN_BOTTOM_MID);

    ui_previousBtn = lv_imgbtn_create(ui_Screen1);
    lv_imgbtn_set_src(ui_previousBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_back_png, NULL);
    lv_imgbtn_set_src(ui_previousBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_back_border_png, NULL);
    lv_obj_set_width(ui_previousBtn, 64);
    lv_obj_set_height(ui_previousBtn, 64);
    lv_obj_set_x(ui_previousBtn, -84);
    lv_obj_set_y(ui_previousBtn, -40);
    lv_obj_set_align(ui_previousBtn, LV_ALIGN_BOTTOM_MID);

    ui_nextBtn = lv_imgbtn_create(ui_Screen1);
    lv_imgbtn_set_src(ui_nextBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_next_png, NULL);
    lv_imgbtn_set_src(ui_nextBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_next_border_png, NULL);
    lv_obj_set_width(ui_nextBtn, 64);
    lv_obj_set_height(ui_nextBtn, 64);
    lv_obj_set_x(ui_nextBtn, 84);
    lv_obj_set_y(ui_nextBtn, -40);
    lv_obj_set_align(ui_nextBtn, LV_ALIGN_BOTTOM_MID);

    ui_volumeBtn = lv_imgbtn_create(ui_Screen1);
    lv_imgbtn_set_src(ui_volumeBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_volume_png, NULL);
    lv_imgbtn_set_src(ui_volumeBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_volume_border_png, NULL);
    lv_obj_set_width(ui_volumeBtn, 64);
    lv_obj_set_height(ui_volumeBtn, 64);
    lv_obj_set_x(ui_volumeBtn, -158);
    lv_obj_set_y(ui_volumeBtn, -40);
    lv_obj_set_align(ui_volumeBtn, LV_ALIGN_BOTTOM_MID);

    ui_muteBtn = lv_imgbtn_create(ui_Screen1);
    lv_imgbtn_set_src(ui_muteBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_mute_png, NULL);
    lv_imgbtn_set_src(ui_muteBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_mute_border_png, NULL);
    lv_obj_set_width(ui_muteBtn, 64);
    lv_obj_set_height(ui_muteBtn, 64);
    lv_obj_set_x(ui_muteBtn, 158);
    lv_obj_set_y(ui_muteBtn, -40);
    lv_obj_set_align(ui_muteBtn, LV_ALIGN_BOTTOM_MID);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);
}
