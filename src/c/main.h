#pragma once

#include <pebble.h>

typedef struct ClaySettings {
    GColor bg_color;
    GColor main_color;
    GColor shadow_color;

} ClaySettings;

Window *main_window;
Layer *bg_layer;
Layer *time_layer;
ClaySettings settings;