#include <pebble.h>
#include "main.h"

static Window *s_main_window;
static BitmapLayer* s_timeline_layers[12];
static BitmapLayer *s_timeborder_layer;
static GBitmap *s_timeborder_bitmap;

int main() {
        init();
        app_event_loop();
        deinit();
}

static void time_handler(struct tm *tick_time, TimeUnits units_changed){
        update_time();
}

static void main_window_load(Window *window) {
        time_t temp = time(NULL); 
        struct tm *current_time = localtime(&temp);
        int hour = current_time->tm_hour % 12;
        window_set_fullscreen(window, true);
        
        s_timeborder_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BACKGROUND);
        s_timeborder_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
        bitmap_layer_set_bitmap(s_timeborder_layer, s_timeborder_bitmap);
        
        
        for(int i = 0; i < hour; i++){
                s_timeline_layers[i] = bitmap_layer_create(GRect(16, i*14 + 1, 144, 13));                
                bitmap_layer_set_background_color(s_timeline_layers[i], GColorBlack);       
                layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_timeline_layers[i]));
        }
        layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_timeborder_layer));
}

static void main_window_unload(Window *window) {
        for(int i = 0; i < 12; i++){
                bitmap_layer_destroy(s_timeline_layers[i]);
        }     
}

static void init() {
        // Create main Window element and assign to pointer
        s_main_window = window_create();
        tick_timer_service_subscribe(MINUTE_UNIT, time_handler);
        // Set handlers to manage the elements inside the Window
        window_set_window_handlers(s_main_window, (WindowHandlers) {
                .load = main_window_load,
                .unload = main_window_unload
        });
        window_stack_push(s_main_window, true);
        update_time();
}

static void update_time() {
        // get a structure that's the current time
        time_t temp = time(NULL); 
        struct tm *current_time = localtime(&temp);
        int hour = current_time->tm_hour % 12;
        int minute =  current_time-> tm_min;
        if(minute > 0){
                bitmap_layer_destroy(s_timeline_layers[hour]);        
        }
        int width = minute * 128 / 60;
        s_timeline_layers[hour] = bitmap_layer_create(GRect(0, hour*14 + 1, width, 13));
        bitmap_layer_set_background_color(s_timeline_layers[hour], GColorBlack);
        layer_add_child(window_get_root_layer(s_main_window), bitmap_layer_get_layer(s_timeline_layers[hour]));
}

static void deinit() {
        window_destroy(s_main_window);
}
