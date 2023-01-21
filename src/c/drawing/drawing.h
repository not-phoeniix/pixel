#pragma once

#include <pebble.h>

// updates time and writes hour and minute to respective variables
void update_time();

/// @brief Draws a pixel on the screen
/// @param x x coord to draw pixel
/// @param y y coord to draw pixel
/// @param color color of pixel
void draw_pixel(int x, int y, GColor color, Layer* layer, GContext *ctx);

// update function for time layer
void time_update_proc(Layer *layer, GContext *ctx);

// update function for bar layer
void bar_update_proc(Layer *layer, GContext *ctx);

// update function for bg layer
void bg_update_proc(Layer *layer, GContext *ctx);