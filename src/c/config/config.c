#include <pebble.h>
#include "config.h"
#include "../main.h"

// setting these variables when nothing is stored in persistent storage
static void set_defaults() {
    // changable by settings page
    settings.bg_color = GColorBlack;
    settings.main_color = GColorWhite;
    settings.shadow_color = GColorRed;

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