#include <pebble.h>

// hi there!
// this watchface was made during the pebble hackathon-001!
// hope you enjoy :)

// window load and unload ===========================================

static void main_window_load(Window *window) {

}

static void main_window_unload(Window *window) {

}

// init and deinit ==================================================

static void init() {

}

static void deinit() {

}

// main =============================================================

int main(void) {
    init();
    app_event_loop();
    deinit();
}