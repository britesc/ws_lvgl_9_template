#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_boot_01;
extern const lv_img_dsc_t img_boot_02;
extern const lv_img_dsc_t img_boot_03;
extern const lv_img_dsc_t img_boot_04;
extern const lv_img_dsc_t img_boot_05;
extern const lv_img_dsc_t img_boot_06;
extern const lv_img_dsc_t img_boot_07;
extern const lv_img_dsc_t img_boot_08;
extern const lv_img_dsc_t img_boot_09;
extern const lv_img_dsc_t img_boot_10;
extern const lv_img_dsc_t img_boot_11;
extern const lv_img_dsc_t img_boot_12;
extern const lv_img_dsc_t img_boot_13;
extern const lv_img_dsc_t img_image_col_settings;
extern const lv_img_dsc_t img_image_col_zap;
extern const lv_img_dsc_t img_image_col_info;
extern const lv_img_dsc_t img_image_col_exit;
extern const lv_img_dsc_t img_image_col_return;
extern const lv_img_dsc_t img_image_col_ear;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[19];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/