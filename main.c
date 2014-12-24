#include <pebble.h>
#include "main.h"
#include <pebble.h>

static Window *s_main_window;
static BitmapLayer* s_timeline_layers[24];
    
int main() {
        init();
        app_event_loop();
        deinit();
}

static void time_handler(struct tm *tick_time, TimeUnits units_changed){
        update_time();
}

static void main_window_load(Window *window) {      
        window_set_fullscreen(window, true);	

        s_timeborder_bitmap = gbitmap_create(RESOURCE_ID_TIMEBORDER);
        s_timeborder_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
        int init = -2;

        for(int i = 0; i < 24; i++){
                s_timeline_layers[i] = bitmap_layer_create(GRect(0, i*7 + 4 + init, 144, 5));
                init = 0;
                bitmap_layer_set_background_color(s_timeline_layers[i], GColorBlack);
                layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_time_layer));
        }     
}

static void main_window_unload(Window *window) {
        text_layer_destroy(s_time_layer);
        text_layer_destroy(s_date_layer);
        text_layer_destroy(s_week_layer);
        for(int i = 0; i < 24; i++){
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

        // write the time to the buffers using the current time
        if(clock_is_24h_style() == true) { 
                strftime(time_buffer, sizeof("00:00"), "%H:%M", current_time);
        } else {
                strftime(time_buffer, sizeof("00:00"), "%I:%M", current_time);
        }
        
        strftime(date_buffer, sizeof("may 01"), "%b %e", current_time);
        strftime(week_buffer, sizeof("wednesday"), "%A", current_time);
}

static void deinit() {
        window_destroy(s_main_window);
}
