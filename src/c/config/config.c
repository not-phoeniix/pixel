#include <pebble.h>
#include "config.h"
#include "../main.h"

// setting these variables when nothing is stored in persistent storage
static void set_defaults() {
    // changable by settings page
        // DEFAULT OPTIONS:
    settings.main_color = GColorWhite;
    settings.shadow_color = GColorRed;
    settings.bg_color_main = GColorBlack;
    settings.bg_color_1 = GColorLightGray;
    settings.bg_color_2 = GColorDarkGray;

    settings.bg_number = 0;
    settings.bar_number = 0;

    settings.do_bt_buzz = false;

    // background global config, not configurable
}

// loading settings from persistent storage
void load_settings() {
    set_defaults();
    persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

// writing settings to the persistent storage
void save_settings() {
    persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}