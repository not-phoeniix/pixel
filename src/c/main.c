#include <pebble.h>
#include "main.h"
#include "drawing/drawing.h"
#include "config/config.h"

// hi there!
// this watchface was made during the pebble hackathon-001!
// hope you enjoy :)

// universal update function ========================================
void update_stuff() {
    //window_set_background_color(main_window, settings.bg_color);
    window_set_background_color(main_window, GColorBlack);

    // redraw all layers
    layer_mark_dirty(time_layer);
}

// handlers =========================================================

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
    layer_mark_dirty(time_layer);
}

// window load and unload ===========================================

static void main_window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(main_window);
    GRect full_bounds = layer_get_bounds(window_layer);

    time_layer = layer_create(full_bounds);
    layer_set_update_proc(time_layer, num_test_proc);
    layer_add_child(window_layer, time_layer);

    update_stuff();
}

static void main_window_unload(Window *window) {
    layer_destroy(time_layer);
}

// init and deinit ==================================================

static void init() {
    main_window = window_create();

    // subscribing to watch services
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

    // setting window load & unload functions
    window_set_window_handlers(main_window, (WindowHandlers){
        .load = main_window_load,
        .unload = main_window_unload
    });

    load_settings();

    window_stack_push(main_window, true);
}

static void deinit() {
    tick_timer_service_unsubscribe();
    window_destroy(main_window);
}

// main =============================================================

int main(void) {
    init();
    app_event_loop();
    deinit();
}