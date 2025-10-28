#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *screen_boot;
    lv_obj_t *screen_no_zap;
    lv_obj_t *screen_zap_entry;
    lv_obj_t *screen_info;
    lv_obj_t *screen_main;
    lv_obj_t *boot_logo;
    lv_obj_t *button_zap;
    lv_obj_t *button_exit;
    lv_obj_t *keyboard_zap_number;
    lv_obj_t *container_main;
    lv_obj_t *button_settings;
    lv_obj_t *container_establish;
    lv_obj_t *button_info;
    lv_obj_t *container_bottom;
    lv_obj_t *label_text_bottom;
    lv_obj_t *button_return_bottom;
    lv_obj_t *container_top;
    lv_obj_t *image_icon_ear;
    lv_obj_t *label_top_container;
    lv_obj_t *label_zap_screen;
    lv_obj_t *container_zap_number;
    lv_obj_t *textarea_zap_number;
    lv_obj_t *container_main_1;
    lv_obj_t *button_settings_1;
    lv_obj_t *container_establish_1;
    lv_obj_t *container_bottom_1;
    lv_obj_t *label_text_bottom_1;
    lv_obj_t *button_return_bottom_1;
    lv_obj_t *container_top_1;
    lv_obj_t *image_icon_ear_1;
    lv_obj_t *label_top_container_1;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SCREEN_BOOT = 1,
    SCREEN_ID_SCREEN_NO_ZAP = 2,
    SCREEN_ID_SCREEN_ZAP_ENTRY = 3,
    SCREEN_ID_SCREEN_INFO = 4,
    SCREEN_ID_SCREEN_MAIN = 5,
};

void create_screen_screen_boot();
void tick_screen_screen_boot();

void create_screen_screen_no_zap();
void tick_screen_screen_no_zap();

void create_screen_screen_zap_entry();
void tick_screen_screen_zap_entry();

void create_screen_screen_info();
void tick_screen_screen_info();

void create_screen_screen_main();
void tick_screen_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/