#include <pebble.h>
#include "drawing.h"
#include "../main.h"
#include "pride.h"

static int hour;
static int min;

/// @brief Updates time and sets char variables to hour and minute
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

/// @brief Draws a singular pixel to the screen given a resolution
/// @param x x position to draw (grid-relative)
/// @param y y position to draw (grid-relative)
/// @param color color of pixel
/// @param bounds screen bounds
void draw_pixel(int x, int y, GColor color, Layer *layer, GContext *ctx) {
    GRect full_bounds = layer_get_bounds(layer);
    GRect dyn_bounds = layer_get_unobstructed_bounds(layer);

    int height_diff = (full_bounds.size.h - dyn_bounds.size.h) / 2;

    GPoint screen_res = {
        .x = full_bounds.size.w,
        .y = full_bounds.size.h
    };

    // width and coordinates to draw pixels
    //   these are calculated as full res, not 
    //   small pixel resolution
    int square_width = screen_res.x / resolution.x;
    int x_coord = x * screen_res.x / resolution.x;
    int y_coord = y * screen_res.y / resolution.y - height_diff;

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
static void draw_number(int number, int x_offset, int y_offset, GColor color, Layer *layer, GContext *ctx) {
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
                draw_pixel(x_offset + w, y_offset + h, color, layer, ctx);
            }

            iteration++;
        }
    }
}

/// @brief Draws the time to the screen
static void draw_time(Layer *layer, GContext *ctx) {
    // splits hour and min variables into 2 separate
        // integers so they can be displayed separately
    int hour2 = (hour == 0) ? 2 : hour % 10;
    int hour1 = (hour == 0) ? 1 : (hour - hour2) / 10;
    int min2 = min % 10;
    int min1 = (min - min2) / 10;

    int x_offset = PBL_IF_ROUND_ELSE(5, 2);
    int y_offset = 11;

    // hours
    draw_number(hour1, x_offset + 1, y_offset, settings.shadow_color, layer, ctx);
    draw_number(hour1, x_offset + 0, y_offset, settings.main_color, layer, ctx);
    draw_number(hour2, x_offset + 6, y_offset, settings.shadow_color, layer, ctx);
    draw_number(hour2, x_offset + 5, y_offset, settings.main_color, layer, ctx);

    // minutes
    draw_number(min1, x_offset + 12, y_offset, settings.shadow_color, layer, ctx);
    draw_number(min1, x_offset + 11, y_offset, settings.main_color, layer, ctx);
    draw_number(min2, x_offset + 17, y_offset, settings.shadow_color, layer, ctx);
    draw_number(min2, x_offset + 16, y_offset, settings.main_color, layer, ctx);
}

// bar drawing functions ============================================

/// @brief Draws the bar in the centered style
/// @param x x position to draw (grid-relative)
/// @param y y position to draw (grid-relative)
static void draw_bar_center(int x, int y, Layer *layer, GContext *ctx) {
    GColor color1 = settings.bg_color_1;
    GColor color2 = settings.bg_color_2;

    for(int i = 0; i < 5; i++) {
        draw_pixel(x + i, y, color2, layer, ctx);
    }

    draw_pixel(x + 5, y, color1, layer, ctx);
    draw_pixel(x + 6, y, color2, layer, ctx);

    draw_pixel(x + 7, y, color1, layer, ctx);
    draw_pixel(x + 8, y, color1, layer, ctx);

    draw_pixel(x + 9, y, color2, layer, ctx);
    draw_pixel(x + 10, y, color1, layer, ctx);

    for(int i = 0; i < 5; i++) {
        draw_pixel(x + 11 + i, y, color2, layer, ctx);
    }
}

/// @brief Draws the bar in the solid style
/// @param x x position to draw (grid-relative)
/// @param y y position to draw (grid-relative)
static void draw_bar_solid(int x, int y, Layer *layer, GContext *ctx) {
    GColor color = settings.bg_color_1;

    for(int i = 0; i < 16; i++) {
        draw_pixel(x + i, y, color, layer, ctx);
    }
}

/// @brief Draws the bar in the dotted style
/// @param x x position to draw (grid-relative)
/// @param y y position to draw (grid-relative)
static void draw_bar_dotted(int x, int y, Layer *layer, GContext *ctx) {
    GColor color1 = settings.bg_color_1;
    GColor color2 = settings.bg_color_2;

    for(int i = 0; i < 16; i += 2) {
        draw_pixel(x + i, y, color1, layer, ctx);
        draw_pixel(x + 1 + i, y, color2, layer, ctx);
    }
}

// bg drawing functions =============================================

/// @brief Draws background with corner-growing pattern, PARENT OF SHINE AND PRIDE
static void draw_bg_corner(GColor color_array[], int num_stripes, Layer *layer, GContext *ctx) {
    int max_x = resolution.x - 1;
    int max_y = resolution.y - 1;
    int counter;
    int num_additional_stripes = PBL_IF_ROUND_ELSE(8, 1);
    int max_stripes = num_stripes + num_additional_stripes;

    // modifying color array ========================================

    // GColor array that holds all colors to be drawn
    GColor colors[max_stripes];

    // adds additional stripes to format on screen better
    //   ONLY ADDS THE FIRST COLOR A FEW TIMES
    for(int i = 0; i < num_additional_stripes; i++) {
        colors[i] = color_array[0];
    }

    // adds main color combo for flag, offset to account
    //   for additional "bump-up" colors in array
    for(int i = 0; i < num_stripes; i++) {
        colors[i + num_additional_stripes] = color_array[i];
    }

    // drawing the corner thingies ==================================

    // top left thingy
    counter = max_stripes;
    for(int y = 0; y < max_stripes; y++) {
        for(int x = 0; x < counter; x++) {
            draw_pixel(x, y, colors[x + (max_stripes - counter)], layer, ctx);
        }
    GRect bounds = layer_get_bounds(layer);
    //GRect bounds = layer_get_unobstructed_bounds(layer);
        counter--;
    }    

    // bottom right thingy
    counter = 0;
    for(int y = max_y; y > (max_y - max_stripes); y--) {
        for(int x = max_x; x > (max_x - max_stripes+ counter); x--) {
            draw_pixel(x, y, colors[max_x - x + counter], layer, ctx);
        }

        counter++;
    }
}

/// @brief Draws background with shine pattern
static void draw_bg_shine(Layer *layer, GContext *ctx) {
    GColor color1 = settings.bg_color_1;
    GColor color2 = settings.bg_color_2;
    GColor color3 = settings.bg_color_main;

    GColor colors[] = {
        color2,
        color1,
        color3,
        color3,
        color2,
        color1
    };

    draw_bg_corner(
        //PBL_IF_ROUND_ELSE(colors_round, colors_rect),
        //PBL_IF_ROUND_ELSE(13, 7),
        colors,
        6,
        layer,
        ctx
    );
}

/// @brief Draws background with grid pattern
static void draw_bg_grid(Layer *layer, GContext *ctx) {
    GColor color1 = settings.bg_color_1;
    GColor color2 = settings.bg_color_main;


    // top grid
    for(int y = 0; y < 6; y++) {
        for(int x = 0; x < resolution.x; x += 2) {
            int offset = x + (y % 2);

            draw_pixel(offset, y, color1, layer, ctx);
            draw_pixel(offset + 1, y, color2, layer, ctx);
        }
    }

    // bottom grid
    for(int y = resolution.y - PBL_IF_ROUND_ELSE(7, 5); y < resolution.y; y++) {
        for(int x = 0; x < resolution.x; x += 2) {
            int offset = x + (y % 2);

            draw_pixel(offset, y, color1, layer, ctx);
            draw_pixel(offset + 1, y, color2, layer, ctx);
        }
    }
}

/// @brief Draws background with pride pattern
static void draw_bg_pride(int stripe_colors[], int num_stripes, Layer *layer, GContext *ctx) {
    GColor colors[num_stripes];
    
    for(int i = 0; i < num_stripes; i++) {
        colors[i] = GColorFromHEX(stripe_colors[i]);
    }

    draw_bg_corner(colors, num_stripes, layer, ctx);
}

/// @brief Draws background with outline pattern
static void draw_bg_outline_rect(Layer *layer, GContext *ctx) {
    GColor color = settings.bg_color_1;

    // top edge
    for(int x = 0; x < resolution.x; x++) {
        draw_pixel(x, 0, color, layer, ctx);
    }

    // bottom edge
    for(int x = 0; x < resolution.x; x++) {
        draw_pixel(x, resolution.y - 1, color, layer, ctx);
    }

    // left edge
    for(int y = 0; y < resolution.y; y++) {
        draw_pixel(0, y, color, layer, ctx);
    }

    // right edge
    for(int y = 0; y < resolution.y; y++) {
        draw_pixel(resolution.x - 1, y, color, layer, ctx);
    }
}

/// @brief Draws background with outline pattern for time round
static void draw_bg_outline_round(Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);

    window_set_background_color(main_window, settings.bg_color_1);

    int distance_from_edge = 7;
    int radius = (bounds.size.w / 2) - distance_from_edge;

    GPoint center = grect_center_point(&bounds);

    graphics_context_set_fill_color(ctx, settings.bg_color_main);

    graphics_fill_circle(ctx, center, radius);
}

// update procs =====================================================

// update function for time layer
void time_update_proc(Layer *layer, GContext *ctx) {
    draw_time(layer, ctx);
}

// update function for bar layer
void bar_update_proc(Layer *layer, GContext *ctx) {
    int x_offset = PBL_IF_ROUND_ELSE(7, 4);
    int y_offset = 9;

    switch(settings.bar_number) {
        // centered style
        case 0:
            draw_bar_center(x_offset, y_offset, layer, ctx);
            draw_bar_center(x_offset, y_offset + 10, layer, ctx);

            break;

        // solid style
        case 1:
            draw_bar_solid(x_offset, y_offset, layer, ctx);
            draw_bar_solid(x_offset, y_offset + 10, layer, ctx);

            break;

        // dotted style
        case 2:
            draw_bar_dotted(x_offset, y_offset, layer, ctx);
            draw_bar_dotted(x_offset, y_offset + 10, layer, ctx);

            break;

        // no bar drawn
        default:
            break;
    }
}

// update function for bg layer
void bg_update_proc(Layer *layer, GContext *ctx) {
    switch(settings.bg_number) {
        // shine bg
        case 0:
            draw_bg_shine(layer, ctx);
            break;

        // grid bg
        case 1:
            draw_bg_grid(layer, ctx);
            break;

        // outline bg
        case 2:
            if(PBL_IS_ROUND) {
                draw_bg_outline_round(layer, ctx);
            } else {
                draw_bg_outline_rect(layer, ctx);
            }

            break;

        // pride bg
        case 3:
            draw_bg_pride(flag_colors[settings.flag_number], num_stripes[settings.flag_number], layer, ctx);
            break;

        // no bg drawn
        default:
            break;
    }
}