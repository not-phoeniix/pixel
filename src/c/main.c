#include <pebble.h>
#include "main.h"
#include "drawing/drawing.h"
#include "config/config.h"
#include "msg/msg.h"

// hi there!
// this watchface was made during the pebble hackathon-001!
// hope you enjoy :)

// universal update function ========================================

void update_stuff() {
    window_set_background_color(main_window, settings.bg_color_main);

    if(PBL_IS_ROUND && settings.bg_number == 2) {
        window_set_background_color(main_window, settings.bg_color_1);
    }

    // redraw all layers
    layer_mark_dirty(time_layer);
    layer_mark_dirty(bar_layer);
    layer_mark_dirty(bg_layer);
}

// handlers/services ================================================

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
    layer_mark_dirty(time_layer);
}

static void bluetooth_callback(bool connected) {
    if(settings.do_bt_buzz && !connected) {
        vibes_short_pulse();
    }
}

// window load and unload ===========================================

static void main_window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(main_window);
    GRect full_bounds = layer_get_bounds(window_layer);

    // main canvas resolution
    resolution = GPoint(
        PBL_IF_ROUND_ELSE(30, 24),
        PBL_IF_ROUND_ELSE(30, 28)
    );

    update_time();

    bg_layer = layer_create(full_bounds);
    layer_set_update_proc(bg_layer, bg_update_proc);
    layer_add_child(window_layer, bg_layer);

    bar_layer = layer_create(full_bounds);
    layer_set_update_proc(bar_layer, bar_update_proc);
    layer_add_child(window_layer, bar_layer);

    time_layer = layer_create(full_bounds);
    layer_set_update_proc(time_layer, time_update_proc);
    layer_add_child(window_layer, time_layer);

    update_stuff();
}

static void main_window_unload(Window *window) {
    layer_destroy(bg_layer);
    layer_destroy(bar_layer);
    layer_destroy(time_layer);
}

// init and deinit ==================================================

static void init() {
    main_window = window_create();

    // subscribing to watch services
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
    connection_service_subscribe((ConnectionHandlers){
        .pebble_app_connection_handler = bluetooth_callback
    });

    // setting window load & unload functions
    window_set_window_handlers(main_window, (WindowHandlers){
        .load = main_window_load,
        .unload = main_window_unload
    });

    init_msg();
    load_settings();

    window_stack_push(main_window, true);

    bluetooth_callback(connection_service_peek_pebble_app_connection());
}

static void deinit() {
    tick_timer_service_unsubscribe();
    connection_service_unsubscribe();
    window_destroy(main_window);
}

// main =============================================================

int main(void) {
    init();
    app_event_loop();
    deinit();
}