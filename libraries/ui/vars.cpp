#include <stdio.h>
#include <lvgl.h>

#include "vars.h"
#include "screens.h"
#include "structs.h"
#include "ui.h"

bool has_valid_zap_number;

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