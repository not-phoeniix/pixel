#include "drawing.h"
#include <pebble.h>
#include "../main.h"

#define PBL_ROUND PBL_IF_ROUND_ELSE(true, false)

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
    int num_array[28];

    switch(number) {
        
        // ONE
        case 1:
            int number[] = {
                0, 1, 1, 1,
                0, 1, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1
            };

            for(int i = 0; i < 28; i++) {
                num_array[i] = number[i];
            }

            break;

        // TWO
        case 2:
            int number[] = {
                1, 1, 1, 1,
                1, 1, 1, 1,
                0, 0, 1, 1,
                1, 1, 1, 1,
                1, 1, 0, 0,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            for(int i = 0; i < 28; i++) {
                num_array[i] = number[i];
            }

            break;

        // THREE
        case 3:
            int number[] = {
                1, 1, 1, 1,
                1, 1, 1, 1,
                0, 0, 1, 1,
                0, 1, 1, 1,
                0, 0, 1, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            for(int i = 0; i < 28; i++) {
                num_array[i] = number[i];
            }

            break;

        // FOUR
        case 4:
            int number[] = {
                1, 0, 1, 1,
                1, 0, 1, 1,
                1, 1, 1, 1,
                1, 1, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1
            };

            for(int i = 0; i < 28; i++) {
                num_array[i] = number[i];
            }

            break;
        
        // FIVE
        case 5:
            int number[] = {
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 1, 0, 0,
                1, 1, 1, 1,
                0, 0, 1, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            for(int i = 0; i < 28; i++) {
                num_array[i] = number[i];
            }

            break;

        // SIX
        case 6:
            int number[] = {
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 1, 0, 0,
                1, 1, 1, 1,
                1, 1, 0, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            for(int i = 0; i < 28; i++) {
                num_array[i] = number[i];
            }

            break;

        // SEVEN
        case 7:
            int number[] = {
                1, 1, 1, 1,
                1, 1, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 1, 1, 0,
                0, 1, 1, 0,
                0, 1, 1, 0
            };

            for(int i = 0; i < 28; i++) {
                num_array[i] = number[i];
            }

            break;

        // EIGHT
        case 8:
            int number[] = {
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 0, 0, 1,
                1, 1, 1, 1,
                1, 0, 0, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            for(int i = 0; i < 28; i++) {
                num_array[i] = number[i];
            }

            break;

        // NINE
        case 9:
            int number[] = {
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 0, 1, 1,
                1, 1, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1,
                0, 0, 1, 1
            };

            for(int i = 0; i < 28; i++) {
                num_array[i] = number[i];
            }

            break;

        // ZERO
        default:
            int number[] = {
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 0, 0, 1,
                1, 1, 1, 1,
                1, 0, 0, 1,
                1, 1, 1, 1,
                1, 1, 1, 1
            };

            for(int i = 0; i < 28; i++) {
                num_array[i] = number[i];
            }

            break;
    }

    // draws each row iteration, top down
    for(int h = 0; h < 7; h++) {
        // draws each row things, left to right
        for(int w = 0; w < 4; w++) {
            draw_pixel(x_offset + w, y_offset + h, color, bounds, ctx);
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

    draw_number(0, 0, 0, GColorWhite, ctx, bounds);
}

// update procs =====================================================

void time_update_proc(Layer *layer, GContext *ctx) {
    draw_time(layer, ctx);
}

void num_test_proc(Layer *layer, GContext *ctx) {
    test_numbers(layer, ctx);
}