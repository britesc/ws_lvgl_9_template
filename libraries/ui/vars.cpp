#include <stdio.h>
#include <string.h>
#include <lvgl.h>

#include "vars.h"
#include "screens.h"
#include "structs.h"
#include "ui.h"

bool has_valid_zap_number;
char textarea_zap_number[100] = { 0 };


void init_vars() {
	has_valid_zap_number = false;
}

void tick_vars() {
    // nothing here, you can add some code here to watch var changes
}



bool get_var_has_valid_zap_number() {
    return has_valid_zap_number;
}

void set_var_has_valid_zap_number(bool value) {
    has_valid_zap_number = value;
}

const char *get_var_textarea_zap_number() {
    return textarea_zap_number;
}

void set_var_textarea_zap_number(const char *value) {
    strncpy(textarea_zap_number, value, sizeof(textarea_zap_number) / sizeof(char));
    textarea_zap_number[sizeof(textarea_zap_number) / sizeof(char) - 1] = 0;
}