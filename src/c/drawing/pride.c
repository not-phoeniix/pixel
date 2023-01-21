#include <pebble.h>
#include "pride.h"
#include "../main.h"

// definitions of each flag's hex code color variables
//   they are reversed from the normal top-down 
//   pattern btw so it draws correctly on the screen
int pride[] = {0xAA00AA, 0x0000FF, 0x00FF00, 0xFFFF00, 0xFFAA00, 0xFF0000};
int trans[] = {0x00AAFF, 0xFF55FF, 0xFFFFFF, 0xFF55FF, 0x00AAFF};
int bisexual[] = {0x0000FF, 0x0000FF, 0xAA55AA, 0xAA0055, 0xAA0055};
int lesbian[] = {0xAA0055, 0xAA00AA, 0xAA55AA, 0xFFFFFF, 0xFFAA00, 0xFF5500, 0xFF0000};
int pansexual[] = {0x00AAFF, 0x00AAFF, 0xFFFF00, 0xFFFF00, 0xFF00FF, 0xFF00FF};
int asexual[] = {0xAA00AA, 0xFFFFFF, 0xAAAAAA, 0x000000};
//int asexual[] = {0x000000, 0xAAAAAA, 0xFFFFFF, 0xAA00AA};     // reversed ace flag
int nonbinary[] = {0x000000, 0xAA55AA, 0xFFFFFF, 0xFFFF55};

// array that puts the above arrays into
int* flag_colors[] = {pride, trans, bisexual, lesbian, pansexual, asexual, nonbinary};
int num_stripes[] = {6, 5, 5, 7, 6, 4, 4};