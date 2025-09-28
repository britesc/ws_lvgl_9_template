#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_red_style() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.red_style = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffe77878), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_max_width(obj, 320, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_max_height(obj, 240, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_min_height(obj, 240, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_min_width(obj, 320, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_win_create(parent_obj);
            lv_obj_set_pos(obj, 70, 86);
            lv_obj_set_size(obj, 311, 239);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 107, 12);
            lv_obj_set_size(obj, 100, 50);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
    }
    
    tick_screen_red_style();
}

void tick_screen_red_style() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_red_style,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_red_style();
}
