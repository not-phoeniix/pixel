#include "drawing.h"
#include <pebble.h>
#include "../main.h"

#define PBL_IS_ROUND PBL_IF_ROUND_ELSE(true, false)
#define PBL_IS_COLOR PBL_IF_COLOR_ELSE(true, false)

static int hour;
static int min;

// PIXEL CANVAS RESOLUTION
// round: 30 x 30
// non-round: 24x28
static GPoint resolution = {
    .x = PBL_IF_ROUND_ELSE(30, 24),
    .y = PBL_IF_ROUND_ELSE(30, 28)
};

/// @brief updates time and sets char variables to hour and minute
void update_time() {
    time_t time_temp = time(NULL);
    struct tm *t = localtime(&time_temp);

    // sets hour depending on watch's 24h setting
    if (clock_is_24h_style()) {
        hour = t->tm_hour;
    } else {
        hour = (t->tm_hour) % 12;
    }

    // sets minute
    min = t->tm_min;
}

// drawing functions ================================================

/// @brief Draws a pixel on the screen
/// @param x x coord to draw pixel
/// @param y y coord to draw pixel
/// @param color color of pixel
static void draw_pixel(int x, int y, GColor color, GRect bounds, GContext *ctx) {
    GPoint screen_res = {
        .x = bounds.size.w,
        .y = bounds.size.h
    };

    // width and coordinates to draw pixels
    int square_width = screen_res.x / resolution.x;
    int x_coord = x * screen_res.x / resolution.x;
    int y_coord = y * screen_res.y / resolution.y;

    // final rect to draw
    GRect pixel = GRect(x_coord, y_coord, square_width, square_width);

    // set color and draw rect
    graphics_context_set_fill_color(ctx, color);
    graphics_fill_rect(ctx, pixel, 0, GCornerNone);
}

/// @brief Draws a number to the screen
/// @param number integer to draw (0 - 9)
/// @param x_offset x coordinate (relative to pixel resolution)
/// @param y_offset y coordinate (relative to pixel resolution)
/// @param color color to draw
static void draw_number(int number, int x_offset, int y_offset, GColor color, GRect bounds, GContext *ctx) {
    int *num_array;

    switch (number) {
        // ONE
        case 1:
            num_array = (int[28]){
                1, 1, 1, 0,
                1, 1, 1, 0,
                0, 1, 1, 0,
                0, 1, 1, 0,
                0, 1, 1, 0,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            break;

        // TWO
        case 2:
            num_array = (int[28]){
                1, 1, 1, 1,
                1, 1, 1, 1,
                0, 0, 1, 1,
                1, 1, 1, 1,
                1, 1, 0, 0,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            break;

        // THREE
        case 3:
            num_array = (int[28]){
                1, 1, 1, 1,
                1, 1, 1, 1,
                0, 0, 1, 1,
                0, 1, 1, 1,
                0, 0, 1, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            break;

        // FOUR
        case 4:
            num_array = (int[28]){
                1, 0, 1, 1,
                1, 0, 1, 1,
                1, 1, 1, 1,
                1, 1, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1
            };

            break;

        // FIVE
        case 5:
            num_array = (int[28]){
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 1, 0, 0,
                1, 1, 1, 1,
                0, 0, 1, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            break;

        // SIX
        case 6:
            num_array = (int[28]){
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 1, 0, 0,
                1, 1, 1, 1,
                1, 1, 0, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            break;

        // SEVEN
        case 7:
            num_array = (int[28]){
                1, 1, 1, 1,
                1, 1, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 1, 1, 0,
                0, 1, 1, 0,
                0, 1, 1, 0
            };

            break;

        // EIGHT
        case 8:
            num_array = (int[28]){
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 0, 0, 1,
                1, 1, 1, 1,
                1, 0, 0, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            break;

        // NINE
        case 9:
            num_array = (int[28]){
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 0, 1, 1,
                1, 1, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1
            };

            break;

        // ZERO
        default:
            num_array = (int[28]){
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 0, 0, 1,
                1, 0, 0, 1,
                1, 0, 0, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            break;
    }

    int iteration = 0;

    // draws each row iteration, top down
    for (int h = 0; h < 7; h++) {
        // draws each pixel in the row, left to right
        for (int w = 0; w < 4; w++) {
            if (num_array[iteration] == 1) {
                draw_pixel(x_offset + w, y_offset + h, color, bounds, ctx);
            }

            iteration++;
        }
    }
}

/// @brief Draws the time to the screen
static void draw_time(Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);

    // splits hour and min variables into 2 separate
        // integers so they can be displayed separately
        // w/ the drawing functions
    int hour2 = hour % 10;
    int hour1 = (hour - hour2) / 10;
    int min2 = min % 10;
    int min1 = (min - min2) / 10;

    // hours
    draw_number(hour1, 3, 11, settings.shadow_color, bounds, ctx);
    draw_number(hour1, 2, 11, settings.main_color, bounds, ctx);
    draw_number(hour2, 8, 11, settings.shadow_color, bounds, ctx);
    draw_number(hour2, 7, 11, settings.main_color, bounds, ctx);

    // minutes
    draw_number(min1, 14, 11, settings.shadow_color, bounds, ctx);
    draw_number(min1, 13, 11, settings.main_color, bounds, ctx);
    draw_number(min2, 19, 11, settings.shadow_color, bounds, ctx);
    draw_number(min2, 18, 11, settings.main_color, bounds, ctx);
}

/// @brief Draws the bar in the centered style
/// @param height height (in relative pixels) to draw it
/// @param inverted whether colors are inverted
static void draw_bar_centered(int height, bool inverted, Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);

    GColor color1 = inverted ? settings.bg_color_2 : settings.bg_color_1;
    GColor color2 = inverted ? settings.bg_color_1 : settings.bg_color_2;

    for(int i = 0; i < 5; i++) {
        draw_pixel(4 + i, height, color2, bounds, ctx);
    }

    draw_pixel(9, height, color1, bounds, ctx);
    draw_pixel(10, height, color2, bounds, ctx);

    draw_pixel(11, height, color1, bounds, ctx);
    draw_pixel(12, height, color1, bounds, ctx);

    draw_pixel(13, height, color2, bounds, ctx);
    draw_pixel(14, height, color1, bounds, ctx);

    for(int i = 0; i < 5; i++) {
        draw_pixel(15 + i, height, color2, bounds, ctx);
    }
}

/// @brief Draws the bar in the solid style
/// @param height height (in relative pixels) to draw it
/// @param inverted whether colors are inverted
static void draw_bar_solid(int height, bool inverted, Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);

    GColor color = inverted ? settings.bg_color_2 : settings.bg_color_1;

    for(int i = 0; i < 16; i++) {
        draw_pixel(4 + i, height, color, bounds, ctx);
    }
}

/// @brief Draws the bar in the dotted style
/// @param height height (in relative pixels) to draw it
/// @param inverted whether colors are inverted
static void draw_bar_dotted(int height, bool inverted, Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);

    GColor color1 = inverted ? settings.bg_color_2 : settings.bg_color_1;
    GColor color2 = inverted ? settings.bg_color_1 : settings.bg_color_2;

    for(int i = 0; i < 16; i += 2) {
        draw_pixel(4 + i, height, color1, bounds, ctx);
        draw_pixel(5 + i, height, color2, bounds, ctx);
    }
}

// update procs =====================================================

void time_update_proc(Layer *layer, GContext *ctx) {
    draw_time(layer, ctx);
}

void bar_update_proc(Layer *layer, GContext *ctx) {
    switch(settings.bar_number) {
        // centered style
        case 0:
            draw_bar_centered(9, settings.invert_bg_colors, layer, ctx);
            draw_bar_centered(19, settings.invert_bg_colors, layer, ctx);

            break;

        // solid style
        case 1:
            draw_bar_solid(9, settings.invert_bg_colors, layer, ctx);
            draw_bar_solid(19, settings.invert_bg_colors, layer, ctx);

            break;

        // dotted style
        case 2:
            draw_bar_dotted(9, settings.invert_bg_colors, layer, ctx);
            draw_bar_dotted(19, !settings.invert_bg_colors, layer, ctx);

            break;

        // no bar drawn
        default:
            break;
    }
}

void bg_update_proc(Layer *layer, GContext *ctx) {
    // hi
}