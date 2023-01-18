#include <pebble.h>
#include "pride.h"
#include "../main.h"

// definitions of each flag's hex code color variables
int pride[] = {0xFF0000, 0xFFAA00, 0xFFFF00, 0x00FF00, 0x0000FF, 0xAA00AA};
int trans[] = {0x00AAFF, 0xFF55FF, 0xFFFFFF, 0xFF55FF, 0x00AAFF};
int bisexual[] = {0xAA0055, 0xAA0055, 0xAA55AA, 0x0000FF, 0x0000FF};
int lesbian[] = {0xFF0000, 0xFF5500, 0xFFAA00, 0xFFFFFF, 0xAA55AA, 0xAA00AA, 0xAA0055};
int pansexual[] = {0xFF00FF, 0xFFFF00, 0x00AAFF};
int asexual[] = {0x000000, 0xAAAAAA, 0xFFFFFF, 0xAA00AA};
int nonbinary[] = {0xFFFF55, 0xFFFFFF, 0xAA55AA, 0x000000};

// array that puts the above arrays into
int* flag_colors[] = {pride, trans, bisexual, lesbian, pansexual, asexual, nonbinary};
int num_stripes[] = {6, 5, 5, 7, 3, 4, 4};