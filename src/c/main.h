#pragma once

#include <pebble.h>

typedef struct ClaySettings {
    GColor main_color;
    GColor shadow_color;
    GColor bg_color_main;
    GColor bg_color_1;
    GColor bg_color_2;
    int bg_number;
    int bar_number;
    bool do_bt_buzz;
} ClaySettings;

Window *main_window;
Layer *bg_layer;
Layer *time_layer;
ClaySettings settings;