#pragma once

#include <pebble.h>

// updates time and writes hour and minute to respective variables
void update_time();

// update function for time layer
void time_update_proc(Layer *layer, GContext *ctx);

// update function for bar layer
void bar_update_proc(Layer *layer, GContext *ctx);