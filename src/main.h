#pragma once

//---------------------------------------------//
//        a graphical watchface.               //
//        by: Charlie Meyer                    //
//        December 2014                        //
//---------------------------------------------//
        
//deals with changing time, calls update time
static void time_handler(struct tm *tick_time, TimeUnits units_changed);
//loads all the app elements and UI
static void main_window_load(Window *window);
//unloads all the app elements and UI 
static void main_window_unload(Window *window);
//the logic to get the time formatted
static void update_time();
//put the UI elements on da heap
//make the event handlers for app_event_loop 
//and push the main window to the window stack 
static void init();
//free everything
static void deinit();