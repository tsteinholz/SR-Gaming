#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
//Dynamic Link
#define ScreenWidth 640
#define ScreenHeight 480
int init();
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;

int main(int argc, char **argv)
{
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR electricBlue = al_map_rgb(44, 117, 255);
    init();
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());

    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        bool redraw = true;

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
        }
        if (event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        }
        if (redraw && al_is_event_queue_empty(queue)) {
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_line(100,200,300,400,yellow, 6);
            float points[8] = { 0, 0, 400, 100, 50, 200, ScreenWidth, ScreenHeight };

            al_draw_triangle(10, 10, 20, 10, 25, 50, al_map_rgb(255, 0, 0), 1.0);
            //al_draw_filled_triangle(10, 10, 20, 10, 25, 50, al_map_rgb(255, 0, 0), 1.0);

            al_draw_rounded_rectangle(10, 10, 100, 100, 5, 5, al_map_rgb(0, 255, 0), 3);
            //al_draw_filled_rounded_rectangle(10, 10, 100, 100, 5, 5, al_map_rgb(0, 255, 0), 3);

            al_draw_rectangle(400, 400, 450, 500, al_map_rgb(255, 98, 100), 9.0);
            //al_draw_filled_rectangle(400, 400, 450, 500, al_map_rgb(255, 98, 100), 9.0);

            al_draw_circle(ScreenWidth / 2, ScreenHeight / 2, 10, al_map_rgb(255, 255, 0), 3.0);
            //al_draw_filled_circle(ScreenWidth / 2, ScreenHeight / 2, 10, al_map_rgb(255, 255, 0), 3.0);

            al_draw_ellipse(ScreenWidth / 2, ScreenHeight - 100, 10, 5, al_map_rgb(255, 0, 255), 4.0);
            //al_draw_filled_ellipse(ScreenWidth / 2, ScreenHeight - 100, 10, 5, al_map_rgb(255, 0, 255), 4.0);

            al_draw_arc(10, ScreenHeight - 100, 10, 0, 4.0, al_map_rgb(255, 0, 0), 2.0);

            al_draw_line(100, 500, 300, 500, electricBlue, 6.0);

            al_draw_pixel(500, 500, electricBlue);

            al_draw_spline(points, electricBlue, 1.0);
            al_flip_display();
        }
    }
   /* al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_line(100,200,300,400,yellow, 6);


    float points[8] = { 0, 0, 400, 100, 50, 200, ScreenWidth, ScreenHeight };

    al_draw_triangle(10, 10, 20, 10, 25, 50, al_map_rgb(255, 0, 0), 1.0);
    //al_draw_filled_triangle(10, 10, 20, 10, 25, 50, al_map_rgb(255, 0, 0), 1.0);

    al_draw_rounded_rectangle(10, 10, 100, 100, 5, 5, al_map_rgb(0, 255, 0), 3);
    //al_draw_filled_rounded_rectangle(10, 10, 100, 100, 5, 5, al_map_rgb(0, 255, 0), 3);

    al_draw_rectangle(400, 400, 450, 500, al_map_rgb(255, 98, 100), 9.0);
    //al_draw_filled_rectangle(400, 400, 450, 500, al_map_rgb(255, 98, 100), 9.0);

    al_draw_circle(ScreenWidth / 2, ScreenHeight / 2, 10, al_map_rgb(255, 255, 0), 3.0);
    //al_draw_filled_circle(ScreenWidth / 2, ScreenHeight / 2, 10, al_map_rgb(255, 255, 0), 3.0);

    al_draw_ellipse(ScreenWidth / 2, ScreenHeight - 100, 10, 5, al_map_rgb(255, 0, 255), 4.0);
    //al_draw_filled_ellipse(ScreenWidth / 2, ScreenHeight - 100, 10, 5, al_map_rgb(255, 0, 255), 4.0);

    al_draw_arc(10, ScreenHeight - 100, 10, 0, 4.0, al_map_rgb(255, 0, 0), 2.0);

    al_draw_line(100, 500, 300, 500, electricBlue, 6.0);

    al_draw_pixel(500, 500, electricBlue);

    al_draw_spline(points, electricBlue, 1.0);
*/
    al_destroy_display(display);

    std::cout << "test";
    return 0;
}

int init(){

    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    display = al_create_display(640, 480);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    al_init_image_addon();
    if(!al_init_primitives_addon()){
        fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    al_install_keyboard();
}
