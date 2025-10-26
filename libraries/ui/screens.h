#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *containers_screen;
    lv_obj_t *zap_screen;
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
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_CONTAINERS_SCREEN = 2,
    SCREEN_ID_ZAP_SCREEN = 3,
};

void create_screen_main();
void tick_screen_main();

void create_screen_containers_screen();
void tick_screen_containers_screen();

void create_screen_zap_screen();
void tick_screen_zap_screen();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/