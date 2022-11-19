#include "drawing.h"
#include <pebble.h>
#include "../main.h"

static char hour_char[] = "hh";
static char min_char[] = "mm";

void update_time() {
    time_t time_temp = time(NULL);
    struct tm *tick_time = localtime(&time_temp);

    strftime(hour_char, sizeof(hour_char), clock_is_24h_style() ? "%H": "%I", tick_time);
    strftime(min_char, sizeof(min_char), "%M", tick_time);
}

// drawing functions ================================================

static void draw_time(Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(layer);

    graphics_context_set_text_color(ctx, settings.main_color);

    GRect textbox = GRect(0, 0, bounds.size.w, bounds.size.h);

    graphics_draw_text(ctx,
        "27",
        fonts_get_system_font(FONT_KEY_LECO_38_BOLD_NUMBERS),
        textbox,
        GTextOverflowModeTrailingEllipsis,
        GTextAlignmentCenter,
        0
    );
}

// update procs =====================================================

void time_update_proc(Layer *layer, GContext *ctx) {
    draw_time(layer, ctx);
}