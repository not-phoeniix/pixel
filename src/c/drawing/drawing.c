#include "drawing.h"
#include <pebble.h>
#include "../main.h"

#define PBL_IS_ROUND PBL_IF_ROUND_ELSE(true, false)

static char hour_char[] = "hh";
static char min_char[] = "mm";

// PIXEL CANVAS RESOLUTION
// round: 30 x 30
// non-round: 24x28
static GPoint resolution = {
    .x = PBL_IF_ROUND_ELSE(30, 24),
    .y = PBL_IF_ROUND_ELSE(30, 28)};

/// @brief updates time and sets char variables to hour and minute
void update_time() {
    time_t time_temp = time(NULL);
    struct tm *tick_time = localtime(&time_temp);

    strftime(hour_char, sizeof(hour_char), clock_is_24h_style() ? "%H" : "%I", tick_time);
    strftime(min_char, sizeof(min_char), "%M", tick_time);
}

// drawing functions ================================================

/// @brief Draws a pixel on the screen
/// @param x x coord to draw pixel
/// @param y y coord to draw pixel
/// @param color color of pixel
/// @param bounds bounds rectangle of screen
/// @param ctx context thingy
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
/// @param ctx context thinfy

static void draw_number(int number, int x_offset, int y_offset, GColor color, GRect bounds, GContext *ctx) {
    int *num_array;

    switch(number) {
        
        // ONE
        case 1:
            num_array = (int[28]) {
                0, 1, 1, 1,
                0, 1, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1
            };

            break;

        // TWO
        case 2:
            num_array = (int[28]) {
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
            num_array = (int[28]) {
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
            num_array = (int[28]) {
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
            num_array = (int[28]) {
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
            num_array = (int[28]) {
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
            num_array = (int[28]) {
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
            num_array = (int[28]) {
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
            num_array = (int[28]) {
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
            num_array = (int[28]) {
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
    for(int h = 0; h < 7; h++) {
        // draws each row things, left to right
        for(int w = 0; w < 4; w++) {
            if(num_array[iteration] == 1) {
                draw_pixel(x_offset + w, y_offset + h, color, bounds, ctx);
            }

            iteration++;
        }
    }
}

/// @brief Draws the time to the screen
static void draw_time(Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(layer);

    graphics_context_set_text_color(ctx, settings.main_color);

    GRect textbox = GRect(0, 0, bounds.size.w, bounds.size.h);

    graphics_draw_text(
        ctx,
        "27",
        fonts_get_system_font(FONT_KEY_LECO_38_BOLD_NUMBERS),
        textbox,
        GTextOverflowModeTrailingEllipsis,
        GTextAlignmentCenter,
        0);
}

static void test_numbers(Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);

    draw_number(0, 0, 3, GColorWhite, bounds, ctx);
    draw_number(1, 5, 3, GColorWhite, bounds, ctx);
    draw_number(2, 10, 3, GColorWhite, bounds, ctx);
    draw_number(3, 15, 3, GColorWhite, bounds, ctx);
    draw_number(4, 20, 3, GColorWhite, bounds, ctx);

    draw_number(5, 0, 12, GColorWhite, bounds, ctx);
    draw_number(6, 5, 12, GColorWhite, bounds, ctx);
    draw_number(7, 10, 12, GColorWhite, bounds, ctx);
    draw_number(8, 15, 12, GColorWhite, bounds, ctx);
    draw_number(9, 20, 12, GColorWhite, bounds, ctx);
}

// update procs =====================================================

void time_update_proc(Layer *layer, GContext *ctx) {
    draw_time(layer, ctx);
}

void num_test_proc(Layer *layer, GContext *ctx) {
    test_numbers(layer, ctx);
}