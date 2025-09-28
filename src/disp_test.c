#include "disp_test.h"

void disp_test() 
{
    lv_obj_t *label = lv_label_create(lv_scr_act());
//    lv_label_set_text(label, "Hello Julian, I'm LVGL! (V" GFX_STR(LVGL_VERSION_MAJOR) "." GFX_STR(LVGL_VERSION_MINOR) "." GFX_STR(LVGL_VERSION_PATCH) ")");
        lv_label_set_text(label, "Hello Julian");

    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *label2 = lv_label_create(lv_scr_act());
    lv_label_set_text(label2, "TEST CODE V2");
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 15);

    lv_obj_t *sw = lv_switch_create(lv_scr_act());
    lv_obj_align(sw, LV_ALIGN_TOP_MID, 0, 40);

    sw = lv_switch_create(lv_scr_act());
    lv_obj_align(sw, LV_ALIGN_BOTTOM_MID, 0, -40);
}