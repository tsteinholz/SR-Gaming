// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main()
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_FONT* century_gothic24;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;

    if(!al_init())
    {
        printf("al_init Failed!\n");
        return -1;
    }
    if(!al_init_primitives_addon())
    {
        printf("al_init_primitives_addon Failed!\n");
        return -1;
    }
    display = al_create_display(640, 480);
    if(!display)
    {
        printf("al_create_display Failed!\n");
        return -1;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    century_gothic24  = al_load_ttf_font("C:\\Windows\\Fonts\\GOTHIC.TTF" , 24, ALLEGRO_ALIGN_CENTRE);

    al_flip_display();

    bool executing = true, up = true;
    int x = 0, y = 0;

    while (executing)
    {
        ALLEGRO_EVENT event;
        bool render;
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            executing = false;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) executing = false;
            break;
        case ALLEGRO_EVENT_TIMER:
            render = true;
            x++;
            if (x > 640) x = 0;
            if (y + 50 >= 480) up = false;
            if (y - 50 <= 0) up = true;
            y += up ? 1 : -1;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            break;
        }

        if (al_is_event_queue_empty(queue) && render)
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_set_target_bitmap(al_get_backbuffer(display));
            ////////////////////////////////////////////////////////////////////

            // Draw Triangle
            al_draw_filled_triangle(10, 10, 200, 200, 350, 230, al_map_rgb(255,0,0));
            // Draw text to the buffer
            al_draw_text(century_gothic24, al_map_rgb(255,255,255), 550, 440, ALLEGRO_ALIGN_CENTRE, "Hello World!");
            // Draw a line to the buffer
            al_draw_line(400,400,500,34,al_map_rgb(255,255,255), 5);
            // Draw a circle
            al_draw_circle(300,300, 50, al_map_rgb(255,255,0), 5);
            // Draw Eclipse
            al_draw_filled_ellipse(500, 300, 40, 56, al_map_rgb(255,0,255));
            // Draw a rectangle
            al_draw_rectangle(100,200,200,300,al_map_rgb(0,255,0), 6);
            // Draw a polygon pt1
            al_draw_filled_rectangle(0,480,50,400,al_map_rgb(25,185,35));
            // Draw a polygon pt2
            al_draw_filled_rectangle(0,480,200,450,al_map_rgb(25,185,35));


            // Moving Circle
            al_draw_circle(x,400, 50, al_map_rgb(55,25,45), 3);
            al_draw_filled_rectangle(100, y-50, 150, y+50,al_map_rgb(65,85,90));

            ////////////////////////////////////////////////////////////////////
            al_flip_display();
        }
        render = false;
    }

    // Destroying the display we created, to avoid memory leaking.
    al_destroy_display(display);

    return 0;
}
