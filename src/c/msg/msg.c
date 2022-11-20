#include <pebble.h>
#include "msg.h"
#include "../main.h"
#include "../config/config.h"

// creates tuples with values of message keys from settings and assigns to setting vars
static void inbox_recieved_handler(DictionaryIterator *iter, void *ctx) {
    Tuple *main_color_t = dict_find(iter, MESSAGE_KEY_main_color);
    if(main_color_t) {
        settings.main_color = GColorFromHEX(main_color_t->value->int32);
    }

    Tuple *shadow_color_t = dict_find(iter, MESSAGE_KEY_shadow_color);
    if(shadow_color_t) {
        settings.shadow_color = GColorFromHEX(shadow_color_t->value->int32);
    }

    Tuple *bg_color_main_t = dict_find(iter, MESSAGE_KEY_bg_color_main);
    if(bg_color_main_t) {
        settings.bg_color_main = GColorFromHEX(bg_color_main_t->value->int32);
    }

    Tuple *bg_color_1_t = dict_find(iter, MESSAGE_KEY_bg_color_1);
    if(bg_color_1_t) {
        settings.bg_color_1 = GColorFromHEX(bg_color_1_t->value->int32);
    }

    Tuple *bg_color_2_t = dict_find(iter, MESSAGE_KEY_bg_color_2);
    if(bg_color_2_t) {
        settings.bg_color_2 = GColorFromHEX(bg_color_2_t->value->int32);
    }

    Tuple *invert_bg_colors_t = dict_find(iter, MESSAGE_KEY_invert_bg_colors);
    if(invert_bg_colors_t) {
        settings.invert_bg_colors = invert_bg_colors_t->value->int32 == 1;
    }

    Tuple *bg_number_t = dict_find(iter, MESSAGE_KEY_bg_number);
    if(bg_number_t) {
        settings.bg_number = atoi(bg_number_t->value->cstring);
    }

    Tuple *bar_number_t = dict_find(iter, MESSAGE_KEY_bar_number);
    if(bar_number_t) {
        settings.bar_number = atoi(bar_number_t->value->cstring);
    }

    Tuple *bt_buzz_t = dict_find(iter, MESSAGE_KEY_do_bt_buzz);
    if(bt_buzz_t) {
        settings.do_bt_buzz = bt_buzz_t->value->int32 == 1;
    }

    save_settings();
    update_stuff();
}

void init_msg() {
    app_message_register_inbox_received(inbox_recieved_handler);

    // calculates buffer size based on how many tuples there are up there ^^
    uint32_t buffer_size = dict_calc_buffer_size(9);

    app_message_open(buffer_size, buffer_size);
}